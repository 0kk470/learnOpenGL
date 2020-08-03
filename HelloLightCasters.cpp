#include "HelloLightCasters.h"

void HelloLightCasters::OnInit()
{
	glEnable(GL_DEPTH_TEST);

	Default_Init();

	//Exercise2_Init();

	//Exercise3_Init();

	//Exercise4_Init();

	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(containerVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void HelloLightCasters::OnRender()
{
	Default_Update();
	//Exercise4_Update();
}

void HelloLightCasters::OnWindowAttach(GLFWwindow* wnd)
{
}

void HelloLightCasters::HandleInput(GLFWwindow* wnd)
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

void HelloLightCasters::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
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

void HelloLightCasters::OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::GetMainCamera()->ProcessMouseScroll(yoffset);
}

void HelloLightCasters::OnDeInit()
{
	delete m_LightingObjShader;
	delete m_LampShader;

	glDeleteVertexArrays(1, &containerVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
}

void HelloLightCasters::Default_Update()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	DrawLightParamWindow();

	auto mainCamera = Camera::GetMainCamera();
	auto lightDir = m_DirectionLightData.lightDirection;
	auto light_ambient = m_DirectionLightData.light_ambient;
	auto light_diffuse = m_DirectionLightData.light_diffuse;
	auto light_specular = m_DirectionLightData.light_specular;
	m_LightingObjShader->Use();
	m_LightingObjShader->setVec3("light.direction", lightDir[0], lightDir[1], lightDir[2]);
	m_LightingObjShader->setVec3("viewPos", mainCamera->Position);

	m_LightingObjShader->setVec3("light.ambient", light_ambient[0], light_ambient[1], light_ambient[2]);
	m_LightingObjShader->setVec3("light.diffuse", light_diffuse[0], light_diffuse[1], light_diffuse[2]);
	m_LightingObjShader->setVec3("light.specular", light_specular[0], light_specular[1], light_specular[2]);

	m_LightingObjShader->setInt("material.diffuse", 0);
	m_LightingObjShader->setInt("material.specular", 1);
	m_LightingObjShader->setFloat("material.shininess", m_DirectionLightData.shininess);

	glm::mat4 view = mainCamera->GetViewMatrix();
	auto projection = glm::perspective(mainCamera->Zoom, 800.0f / 600.0f, 0.1f, 100.0f);

	m_LightingObjShader->setMat4("view", view);
	m_LightingObjShader->setMat4("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, SpecularTex);

	glBindVertexArray(containerVAO);

	for(int i = 0; i < cubePositions.size(); ++i)
	{
		glm::mat4 TempModel(1);
		TempModel = glm::translate(TempModel, cubePositions[i]);
		TempModel = glm::rotate(TempModel, glm::radians(i * 20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		m_LightingObjShader->setMat4("model", TempModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);

	//m_LampShader->Use();

	//m_LampShader->setMat4("projection", projection);
	//m_LampShader->setMat4("view", view);
	//glm::mat4 model(1);
	//auto lightPos = m_DirectionLightData.lightPos;
	//model = glm::translate(model, glm::vec3(lightPos[0], lightPos[1], lightPos[2]));
	//model = glm::scale(model, glm::vec3(0.2f));

	//m_LampShader->setMat4("model", model);
	//m_LampShader->setVec3("lightColor", lightColor[0], lightColor[1], lightColor[2]);
	//glBindVertexArray(lightVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(0);
}

void HelloLightCasters::DrawLightParamWindow()
{
	ImGui::SetNextWindowPos(ImVec2(800, 600), 0, ImVec2(1, 1));
	ImGui::Begin("Light Modifier", 0, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::BulletText("Cube Attribute");
	ImGui::SliderInt("shininess", &m_DirectionLightData.shininess, 0, 256);
	ImGui::BulletText("DirectionLightLight Attribute");
	ImGui::DragFloat3("Direction ", m_DirectionLightData.lightDirection, 0.05f, -1, 1);
	ImGui::DragFloat3("Ambient ", m_DirectionLightData.light_ambient, 0.05f, 0, 1);
	ImGui::DragFloat3("Diffuse ", m_DirectionLightData.light_diffuse, 0.05f, 0, 1);
	ImGui::DragFloat3("Specular ", m_DirectionLightData.light_specular, 0.05f, 0, 1);
	ImGui::End();
}

void HelloLightCasters::Default_Init()
{
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloLightCasters/Cube.vertex", "./Shaders/Fragment/HelloLightCasters/Cube.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloLightCasters/Light.vertex", "./Shaders/Fragment/HelloLightCasters/Light.frag");

	diffuseTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest.png");
	SpecularTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest_specular.png");
}

void HelloLightCasters::Exercise2_Init()
{
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloLightCasters/Cube.vertex", "./Shaders/Fragment/HelloLightCasters/Cube_Exercise2.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloLightCasters/Light.vertex", "./Shaders/Fragment/HelloLightCasters/Light.frag");

	diffuseTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest.png");
	SpecularTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest_specular.png");
}

void HelloLightCasters::Exercise3_Init()
{
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloLightCasters/Cube.vertex", "./Shaders/Fragment/HelloLightCasters/Cube.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloLightCasters/Light.vertex", "./Shaders/Fragment/HelloLightCasters/Light.frag");

	diffuseTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest.png");
	SpecularTex = Resource::LoadTexture("./resources/HelloLightMap/lighting_maps_specular_color.png");
}

void HelloLightCasters::Exercise4_Init()
{
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloLightCasters/Cube.vertex", "./Shaders/Fragment/HelloLightCasters/Cube_Exercise4.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloLightCasters/Light.vertex", "./Shaders/Fragment/HelloLightCasters/Light.frag");

	diffuseTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest.png");
	SpecularTex = Resource::LoadTexture("./resources/HelloLightMap/lighting_maps_specular_color.png");
	EmissionMapTex = Resource::LoadTexture("./resources/HelloLightMap/matrix.jpg");
}

void HelloLightCasters::Exercise4_Update()
{

}
