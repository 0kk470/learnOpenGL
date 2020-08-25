#include "Blending.h"

const float SCR_WIDTH = 800;

const float SCR_HEIGHT = 600;

void Blending::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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


	glGenVertexArrays(1, &transparentVAO);
	glGenBuffers(1, &transparentVBO);
	glBindVertexArray(transparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);


	cubeTexture = Resource::LoadTexture("./resources/DepthTest/marble.jpg");
	floorTexture = Resource::LoadTexture("./resources/DepthTest/metal.png");
	grassTexture = Resource::LoadTexture("./resources/Blending/grass.png", GL_CLAMP_TO_EDGE);
	windowTexture = Resource::LoadTexture("./resources/Blending/blending_transparent_window.png");

	m_NormalShader = new Shader("./Shaders/Vertex/DepthTest/DepthTest.vertex", "./Shaders/Fragment/DepthTest/DepthTest.frag");

	m_GrassShader = new Shader("./Shaders/Vertex/Blending/Blending.vertex", "./Shaders/Fragment/Blending/Grass.frag");
	m_WindowShader = new Shader("./Shaders/Vertex/StencilTest/StencilTest.vertex", "./Shaders/Fragment/StencilTest/StencilTest.frag");
}

void Blending::OnRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawBorderParamWindow();

	auto camera = Camera::GetMainCamera();
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	m_NormalShader->Use();
	m_NormalShader->setMat4("view", view);
	m_NormalShader->setMat4("projection", projection);
	m_WindowShader->Use();
	m_WindowShader->setMat4("view", view);
	m_WindowShader->setMat4("projection", projection);
	m_GrassShader->Use();
	m_GrassShader->setMat4("view", view);
	m_GrassShader->setMat4("projection", projection);

	DrawFloor();

	DrawCubes();

	DrawGrass();

	DrawTransparentWindow();
}


void Blending::DrawCubes()
{
	m_NormalShader->Use();
	glm::mat4 model = glm::mat4(1.0f);
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	m_NormalShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	m_NormalShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Blending::DrawGrass()
{
	if (!isDrawingGrass)
		return;
	m_GrassShader->Use();
	m_GrassShader->setInt("texture1", 0);
	glBindVertexArray(transparentVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	auto model = glm::mat4(1.0f);

	for (unsigned int i = 0; i < vegetation.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, vegetation[i]);
		m_GrassShader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Blending::DrawTransparentWindow()
{
	if (!isDrawingTransparentWindow)
		return;
	m_NormalShader->Use();
	m_NormalShader->setInt("texture1", 0);
	glBindVertexArray(transparentVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, windowTexture);
	auto model = glm::mat4(1.0f);
	auto sortedPositions = vegetation;

	std::sort(sortedPositions.begin(), sortedPositions.end(),
		[](const glm::vec3& pos1, const glm::vec3& pos2)
		{
			float dis1 = glm::distance(pos1, Camera::GetMainCamera()->Position);
			float dis2 = glm::distance(pos2, Camera::GetMainCamera()->Position);
			return dis1 > dis2;
		});
	for (unsigned int i = 0; i < sortedPositions.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, sortedPositions[i]);
		m_NormalShader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Blending::DrawFloor()
{
	m_NormalShader->Use();
	glBindVertexArray(planeVAO);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	m_NormalShader->setMat4("model", glm::mat4(1.0f));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Blending::DrawBorderParamWindow()
{
	ImGui::SetNextWindowPos(ImVec2(800, 600), 0, ImVec2(1, 1));
	ImGui::Begin("Blending Modifier", 0, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Draw Grass", &isDrawingGrass);
	ImGui::Checkbox("Draw Windows", &isDrawingTransparentWindow);
	ImGui::End();
}


void Blending::OnWindowAttach(GLFWwindow* wnd)
{
}

void Blending::HandleInput(GLFWwindow* wnd)
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

void Blending::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
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

void Blending::OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::GetMainCamera()->ProcessMouseScroll(yoffset);
}

void Blending::OnDeInit()
{
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &planeVBO);
	glDeleteBuffers(1, &transparentVBO);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteVertexArrays(1, &transparentVAO);

	glDeleteTextures(1, &cubeTexture);
	glDeleteTextures(1, &floorTexture);
	glDeleteTextures(1, &grassTexture);
	glDeleteTextures(1, &windowTexture);

	delete m_NormalShader;
	delete m_GrassShader;
	delete m_WindowShader;
}
