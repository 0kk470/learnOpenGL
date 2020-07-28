#include "HelloMaterial.h"

void HelloMaterial::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	//Default Shader
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloMaterial/Cube.vertex", "./Shaders/Fragment/HelloMaterial/Cube.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloMaterial/Light.vertex", "./Shaders/Fragment/HelloMaterial/Light.frag");


	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(containerVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void HelloMaterial::OnRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	DrawLightParamWindow();

	auto mainCamera = Camera::GetMainCamera();
	m_LightingObjShader->Use();
	m_LightingObjShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	m_LightingObjShader->setVec3("lightColor", lightColor[0], lightColor[1], lightColor[2]);
	m_LightingObjShader->setVec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);
	m_LightingObjShader->setVec3("viewPos", mainCamera->Position);

	m_LightingObjShader->setFloat("ambientStrength", ambient);
	m_LightingObjShader->setInt("shininess", shininess);
	m_LightingObjShader->setFloat("specularStrength", specularStrength);

	glm::mat4 view = mainCamera->GetViewMatrix();
	auto projection = glm::perspective(mainCamera->Zoom, 800.0f / 600.0f, 0.1f, 100.0f);

	glm::mat4 model(1);
	m_LightingObjShader->setMat4("model", model);
	m_LightingObjShader->setMat4("view", view);
	m_LightingObjShader->setMat4("projection", projection);


	glBindVertexArray(containerVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	m_LampShader->Use();

	m_LampShader->setMat4("projection", projection);
	m_LampShader->setMat4("view", view);
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(lightPos[0], lightPos[1], lightPos[2]));
	model = glm::scale(model, glm::vec3(0.2f));

	m_LampShader->setMat4("model", model);
	m_LampShader->setVec3("lightColor", lightColor[0], lightColor[1], lightColor[2]);
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void HelloMaterial::OnWindowAttach(GLFWwindow* wnd)
{
}

void HelloMaterial::HandleInput(GLFWwindow* wnd)
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

void HelloMaterial::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	Camera::GetMainCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void HelloMaterial::OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::GetMainCamera()->ProcessMouseScroll(yoffset);
}

void HelloMaterial::OnDeInit()
{
	delete m_LightingObjShader;
	delete m_LampShader;
}

void HelloMaterial::DrawLightParamWindow()
{
	ImGui::SetNextWindowPos(ImVec2(800, 600), 0, ImVec2(1, 1));
	ImGui::Begin("Light Modifier", 0, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::ColorEdit3("light color", lightColor);
	ImGui::DragFloat3("Light Pos", lightPos, 0.3f);
	ImGui::SliderFloat("Diffuse Strength", &ambient, 0, 1);
	ImGui::SliderFloat("Specular Strength", &specularStrength, 0, 1);
	ImGui::SliderInt("shininess", &shininess, 0, 256);
	ImGui::End();
}

void HelloMaterial::basic_light_exercise3()
{
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloMaterial/basic_light_exercise3.vertex", "./Shaders/Fragment/HelloMaterial/basic_light_exercise3.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloMaterial/lamp.vertex", "./Shaders/Fragment/HelloMaterial/lamp.frag");
}

void HelloMaterial::basic_light_exercise4()
{
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloMaterial/basic_light_exercise4.vertex", "./Shaders/Fragment/HelloMaterial/basic_light_exercise4.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloMaterial/lamp.vertex", "./Shaders/Fragment/HelloMaterial/lamp.frag");
}
