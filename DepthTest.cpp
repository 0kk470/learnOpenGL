#include "DepthTest.h"

const float SCR_WIDTH = 800;

const float SCR_HEIGHT = 600;

void DepthTest::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);


	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	cubeTexture = Resource::LoadTexture("./resources/DepthTest/marble.jpg");
	floorTexture = Resource::LoadTexture("./resources/DepthTest/metal.png");

	m_DepthShader = new Shader("./Shaders/Vertex/DepthTest/DepthTest.vertex", "./Shaders/Fragment/DepthTest/DepthTest.frag");
}

void DepthTest::OnRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawDepthTestWindow();

	m_DepthShader->Use();
	auto camera = Camera::GetMainCamera();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	m_DepthShader->setMat4("view", view);
	m_DepthShader->setMat4("projection", projection);

	// cubes
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	m_DepthShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	m_DepthShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	// floor
	glBindVertexArray(planeVAO);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	m_DepthShader->setMat4("model", glm::mat4(1.0f));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void DepthTest::OnWindowAttach(GLFWwindow* wnd)
{
}

void DepthTest::HandleInput(GLFWwindow* wnd)
{
	GLfloat deltaTime = Time::deltaTime;
	auto mainCamera = Camera::GetMainCamera();
	if (glfwGetKey(wnd, GLFW_KEY_W))
	{
		mainCamera->ProcessKeyboard(FORWARD, deltaTime);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_S))
	{
		mainCamera->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(wnd, GLFW_KEY_A))
	{
		mainCamera->ProcessKeyboard(LEFT, deltaTime);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_D))
	{
		mainCamera->ProcessKeyboard(RIGHT, deltaTime);
	}
}

void DepthTest::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (Mouse::IsFisrtMove())
	{
		Mouse::SetLastXY(xpos, ypos);
		Mouse::SetFirstMove(false);
	}

	GLfloat xoffset = xpos - Mouse::GetLastX();
	GLfloat yoffset = Mouse::GetLastY() - ypos;  // Reversed since y-coordinates go from bottom to left

	Mouse::SetLastXY(xpos, ypos);

	Camera::GetMainCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void DepthTest::OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::GetMainCamera()->ProcessMouseScroll(yoffset);
}

void DepthTest::DrawDepthTestWindow()
{
	ImGui::SetNextWindowPos(ImVec2(800, 600), 0, ImVec2(1, 1));
	ImGui::Begin("DepthTest Modifier", 0, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("IsEnableDepthTest", &isEnableDepthTest);
	if (isEnableDepthTest && !glIsEnabled(GL_DEPTH_TEST))
	{
		glEnable(GL_DEPTH_TEST);
	}
	else if(!isEnableDepthTest && glIsEnabled(GL_DEPTH_TEST))
	{
		glDisable(GL_DEPTH_TEST);
	}
	ImGui::Combo("Functions", &CurrentDepthFuncIndex, FuncItemsName, GL_ALWAYS - GL_NEVER + 1);
	glDepthFunc(FuncItems[CurrentDepthFuncIndex]);
	ImGui::End();
}

void DepthTest::OnDeInit()
{
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &planeVBO);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &planeVAO);

	glDeleteTextures(1, &cubeTexture);
	glDeleteTextures(1, &floorTexture);

	delete m_DepthShader;
}
