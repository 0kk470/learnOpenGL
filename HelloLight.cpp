#include "HelloLight.h"

void HelloLight::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloLight/lighting.vertex", "./Shaders/Fragment/HelloLight/lighting.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloLight/lamp.vertex", "./Shaders/Fragment/HelloLight/lamp.frag");

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

void HelloLight::OnRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	m_LightingObjShader->Use();
	m_LightingObjShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	m_LightingObjShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	m_LightingObjShader->setVec3("lightPos", lightPos);

	auto mainCamera = Camera::GetMainCamera();
	glm::mat4 view = mainCamera->GetViewMatrix();
	auto projection = glm::perspective(mainCamera->Zoom, 800.0f / 600.0f, 0.1f, 100.0f);

	m_LightingObjShader->setMat4("projection", projection);
	m_LightingObjShader->setMat4("view", view);

	glm::mat4 model(1);
	m_LightingObjShader->setMat4("model", model);

	glBindVertexArray(containerVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	m_LampShader->Use();

	m_LampShader->setMat4("projection", projection);
	m_LampShader->setMat4("view", view);
	model = glm::mat4(1);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); 

	m_LampShader->setMat4("model", model);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void HelloLight::OnWindowAttach(GLFWwindow* wnd)
{
}

void HelloLight::HandleInput(GLFWwindow* wnd)
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

void HelloLight::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
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

void HelloLight::OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::GetMainCamera()->ProcessMouseScroll(yoffset);
}

void HelloLight::OnDeInit()
{
	delete m_LightingObjShader;
	delete m_LampShader;
}
