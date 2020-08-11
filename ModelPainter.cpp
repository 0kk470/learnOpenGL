#include "ModelPainter.h"

void ModelPainter::OnInit()
{
	glEnable(GL_DEPTH_TEST);

	Default_Init();

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

void ModelPainter::OnRender()
{
	Default_Update();
}

void ModelPainter::OnWindowAttach(GLFWwindow* wnd)
{
}

void ModelPainter::HandleInput(GLFWwindow* wnd)
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

void ModelPainter::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
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

void ModelPainter::OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::GetMainCamera()->ProcessMouseScroll(yoffset);
}

void ModelPainter::OnDeInit()
{
	delete m_LightingObjShader;
	delete m_LampShader;

	glDeleteVertexArrays(1, &containerVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
}

void ModelPainter::Default_Update()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	DrawLightParamWindow();

	auto mainCamera = Camera::GetMainCamera();
	m_LightingObjShader->Use();
	m_LightingObjShader->setVec3("viewPos", mainCamera->Position);
	m_LightingObjShader->setInt("material.diffuse", 0);
	m_LightingObjShader->setInt("material.specular", 1);
	m_LightingObjShader->setFloat("material.shininess", shininess);

	glm::mat4 view = mainCamera->GetViewMatrix();
	auto projection = glm::perspective(mainCamera->Zoom, SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

	m_LightingObjShader->setMat4("view", view);
	m_LightingObjShader->setMat4("projection", projection);

	//Direction Light
	m_LightingObjShader->setVec3("dirLight.direction", m_DirLight.lightDirection[0], m_DirLight.lightDirection[1], m_DirLight.lightDirection[2]);
	m_LightingObjShader->setVec3("dirLight.ambient", m_DirLight.light_ambient[0], m_DirLight.light_ambient[1], m_DirLight.light_ambient[2]);
	m_LightingObjShader->setVec3("dirLight.diffuse", m_DirLight.light_diffuse[0], m_DirLight.light_diffuse[1], m_DirLight.light_diffuse[2]);
	m_LightingObjShader->setVec3("dirLight.specular", m_DirLight.light_specular[0], m_DirLight.light_specular[1], m_DirLight.light_specular[2]);
	m_LightingObjShader->setBool("dirLight.isOn", m_DirLight.IsOn);

	//Point Light
	for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
	{
		m_LightingObjShader->setVec3(StringUtil::Format("pointlights[%d].Position", i), m_PointLights[i]->Position[0], m_PointLights[i]->Position[1], m_PointLights[i]->Position[2]);
		m_LightingObjShader->setVec3(StringUtil::Format("pointlights[%d].ambient", i), m_PointLights[i]->Ambient[0], m_PointLights[i]->Ambient[1], m_PointLights[i]->Ambient[2]);
		m_LightingObjShader->setVec3(StringUtil::Format("pointlights[%d].diffuse", i), m_PointLights[i]->Diffuse[0], m_PointLights[i]->Diffuse[1], m_PointLights[i]->Diffuse[2]);
		m_LightingObjShader->setVec3(StringUtil::Format("pointlights[%d].specular", i), m_PointLights[i]->Specular[0], m_PointLights[i]->Specular[1], m_PointLights[i]->Specular[2]);
		m_LightingObjShader->setFloat(StringUtil::Format("pointlights[%d].constant", i), 1);
		m_LightingObjShader->setFloat(StringUtil::Format("pointlights[%d].linear", i), m_PointLights[i]->linear);
		m_LightingObjShader->setFloat(StringUtil::Format("pointlights[%d].quadratic", i), m_PointLights[i]->quadratic);
		m_LightingObjShader->setBool(StringUtil::Format("pointlights[%d].isOn", i), m_PointLights[i]->isOn);
	}

	//Spot Light
	m_LightingObjShader->setVec3("spotLight.Position", mainCamera->Position);
	m_LightingObjShader->setVec3("spotLight.direction", mainCamera->Front);
	m_LightingObjShader->setVec3("spotLight.ambient", m_CameraSpotLight.Ambient[0], m_CameraSpotLight.Ambient[1], m_CameraSpotLight.Ambient[2]);
	m_LightingObjShader->setVec3("spotLight.diffuse", m_CameraSpotLight.Diffuse[0], m_CameraSpotLight.Diffuse[1], m_CameraSpotLight.Diffuse[2]);
	m_LightingObjShader->setVec3("spotLight.specular", m_CameraSpotLight.Specular[0], m_CameraSpotLight.Specular[1], m_CameraSpotLight.Specular[2]);
	m_LightingObjShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(m_CameraSpotLight.cutOff)));
	m_LightingObjShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(m_CameraSpotLight.outerCutOff)));
	m_LightingObjShader->setFloat("spotLight.constant", 1);
	m_LightingObjShader->setFloat("spotLight.linear", m_CameraSpotLight.linear);
	m_LightingObjShader->setFloat("spotLight.quadratic", m_CameraSpotLight.quadratic);
	m_LightingObjShader->setBool("spotLight.isOn", m_CameraSpotLight.isOn);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, SpecularTex);

	glBindVertexArray(containerVAO);

	for (int i = 0; i < cubePositions.size(); ++i)
	{
		glm::mat4 TempModel(1);
		TempModel = glm::translate(TempModel, cubePositions[i]);
		TempModel = glm::rotate(TempModel, glm::radians(i * 20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		m_LightingObjShader->setMat4("model", TempModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);

	m_LampShader->Use();

	m_LampShader->setMat4("projection", projection);
	m_LampShader->setMat4("view", view);
	glBindVertexArray(lightVAO);
	for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
	{
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(m_PointLights[i]->Position[0], m_PointLights[i]->Position[1], m_PointLights[i]->Position[2]));
		model = glm::scale(model, glm::vec3(0.2f));

		m_LampShader->setMat4("model", model);
		if (m_PointLights[i]->isOn)
			m_LampShader->setVec3("lightColor", m_PointLights[i]->Ambient[0], m_PointLights[i]->Ambient[1], m_PointLights[i]->Ambient[2]);
		else
			m_LampShader->setVec3("lightColor", glm::vec3(0));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);


	//Prophet's Model Render
	DrawProphet(view, projection);
}

void ModelPainter::DrawLightParamWindow()
{
	ImGui::SetNextWindowPos(ImVec2(800, 600), 0, ImVec2(1, 1));
	ImGui::Begin("Light Modifier", 0, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::BulletText("Cube Attribute");
	ImGui::SliderInt("shininess", &shininess, 0, 256);

	ImGui::BulletText("DirectionLight Attribute");
	ImGui::Checkbox("DirLight IsOn ", &m_DirLight.IsOn);
	ImGui::DragFloat3("DirLight Direction ", m_DirLight.lightDirection, 0.05f, -1, 1);
	ImGui::DragFloat3("DirLight Ambient ", m_DirLight.light_ambient, 0.05f, 0, 1);
	ImGui::DragFloat3("DirLight Diffuse ", m_DirLight.light_diffuse, 0.05f, 0, 1);
	ImGui::DragFloat3("DirLight Specular ", m_DirLight.light_specular, 0.05f, 0, 1);

	ImGui::BulletText("PointLight Attribute");
	for (int i = 0; i < m_PointLights.size(); ++i)
	{
		auto pLight = m_PointLights[i];
		ImGui::Text("PointLight %d", i + 1);
		ImGui::PushID(i);
		ImGui::Checkbox("IsOn", &pLight->isOn);
		if (pLight->isOn)
		{
			ImGui::DragFloat3("Position ", pLight->Position, 0.05f);
			ImGui::DragFloat3("Ambient ", pLight->Ambient, 0.05f, 0, 1);
			ImGui::DragFloat3("Diffuse ", pLight->Diffuse, 0.05f, 0, 1);
			ImGui::DragFloat3("Specular ", pLight->Specular, 0.05f, 0, 1);
			ImGui::DragFloat("linear", &pLight->linear, 0.005f, 0.001f, 1);
			ImGui::DragFloat("quadratic", &pLight->quadratic, 0.005f, 0.001f, 1);
		}
		ImGui::PopID();
	}

	ImGui::BulletText("Camera SpotLight Attribute");
	ImGui::Checkbox("Spot IsOn ", &m_CameraSpotLight.isOn);
	//ImGui::DragFloat3("Spot Direction ", m_CameraSpotLight.direction, 0.05f, -1, 1);
	ImGui::DragFloat3("Spot Ambient ", m_CameraSpotLight.Ambient, 0.05f, 0, 1);
	ImGui::DragFloat3("Spot Diffuse ", m_CameraSpotLight.Diffuse, 0.05f, 0, 1);
	ImGui::DragFloat3("Spot Specular ", m_CameraSpotLight.Specular, 0.05f, 0, 1);
	ImGui::DragFloat("Spot linear", &m_CameraSpotLight.linear, 0.005f, 0.001f, 1);
	ImGui::DragFloat("Spot quadratic", &m_CameraSpotLight.quadratic, 0.005f, 0.001f, 1);
	ImGui::DragFloat("Spot cutOff", &m_CameraSpotLight.cutOff, 1, 5, m_CameraSpotLight.outerCutOff);
	ImGui::DragFloat("Spot outerCutOff", &m_CameraSpotLight.outerCutOff, 1, m_CameraSpotLight.cutOff, 45);

	ImGui::End();
}

void ModelPainter::DrawProphet(glm::mat4 view , glm::mat4 projection)
{

	auto mainCamera = Camera::GetMainCamera();
	m_ProphetShader->Use();
	m_ProphetShader->setMat4("projection", projection);
	m_ProphetShader->setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.55f, 0.0f));
	model = glm::scale(model, glm::vec3(0.005f));
	m_ProphetShader->setMat4("model", model);
	m_ProphetShader->setFloat("shininess", shininess);
	m_Prophet->Draw(*m_ProphetShader);
	m_ProphetShader->setVec3("dirLight.direction", m_DirLight.lightDirection[0], m_DirLight.lightDirection[1], m_DirLight.lightDirection[2]);
	m_ProphetShader->setVec3("dirLight.ambient", m_DirLight.light_ambient[0], m_DirLight.light_ambient[1], m_DirLight.light_ambient[2]);
	m_ProphetShader->setVec3("dirLight.diffuse", m_DirLight.light_diffuse[0], m_DirLight.light_diffuse[1], m_DirLight.light_diffuse[2]);
	m_ProphetShader->setVec3("dirLight.specular", m_DirLight.light_specular[0], m_DirLight.light_specular[1], m_DirLight.light_specular[2]);
	m_ProphetShader->setBool("dirLight.isOn", m_DirLight.IsOn);

	//Point Light
	for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
	{
		m_ProphetShader->setVec3(StringUtil::Format("pointlights[%d].Position", i), m_PointLights[i]->Position[0], m_PointLights[i]->Position[1], m_PointLights[i]->Position[2]);
		m_ProphetShader->setVec3(StringUtil::Format("pointlights[%d].ambient", i), m_PointLights[i]->Ambient[0], m_PointLights[i]->Ambient[1], m_PointLights[i]->Ambient[2]);
		m_ProphetShader->setVec3(StringUtil::Format("pointlights[%d].diffuse", i), m_PointLights[i]->Diffuse[0], m_PointLights[i]->Diffuse[1], m_PointLights[i]->Diffuse[2]);
		m_ProphetShader->setVec3(StringUtil::Format("pointlights[%d].specular", i), m_PointLights[i]->Specular[0], m_PointLights[i]->Specular[1], m_PointLights[i]->Specular[2]);
		m_ProphetShader->setFloat(StringUtil::Format("pointlights[%d].constant", i), 1);
		m_ProphetShader->setFloat(StringUtil::Format("pointlights[%d].linear", i), m_PointLights[i]->linear);
		m_ProphetShader->setFloat(StringUtil::Format("pointlights[%d].quadratic", i), m_PointLights[i]->quadratic);
		m_ProphetShader->setBool(StringUtil::Format("pointlights[%d].isOn", i), m_PointLights[i]->isOn);
	}

	//Spot Light
	m_ProphetShader->setVec3("spotLight.Position", mainCamera->Position);
	m_ProphetShader->setVec3("spotLight.direction", mainCamera->Front);
	m_ProphetShader->setVec3("spotLight.ambient", m_CameraSpotLight.Ambient[0], m_CameraSpotLight.Ambient[1], m_CameraSpotLight.Ambient[2]);
	m_ProphetShader->setVec3("spotLight.diffuse", m_CameraSpotLight.Diffuse[0], m_CameraSpotLight.Diffuse[1], m_CameraSpotLight.Diffuse[2]);
	m_ProphetShader->setVec3("spotLight.specular", m_CameraSpotLight.Specular[0], m_CameraSpotLight.Specular[1], m_CameraSpotLight.Specular[2]);
	m_ProphetShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(m_CameraSpotLight.cutOff)));
	m_ProphetShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(m_CameraSpotLight.outerCutOff)));
	m_ProphetShader->setFloat("spotLight.constant", 1);
	m_ProphetShader->setFloat("spotLight.linear", m_CameraSpotLight.linear);
	m_ProphetShader->setFloat("spotLight.quadratic", m_CameraSpotLight.quadratic);
	m_ProphetShader->setBool("spotLight.isOn", m_CameraSpotLight.isOn);
}

void ModelPainter::Default_Init()
{
	m_LightingObjShader = new Shader("./Shaders/Vertex/HelloLightCasters/Cube.vertex", "./Shaders/Fragment/HelloLightCasters/Cube.frag");
	m_LampShader = new Shader("./Shaders/Vertex/HelloLightCasters/Light.vertex", "./Shaders/Fragment/HelloLightCasters/Light.frag");
	m_ProphetShader = new Shader("./Shaders/Vertex/Model/Cube.vertex", "./Shaders/Fragment/Model/Cube.frag");
	m_Prophet = new Model("./resources/paladin_j_nordstrom.fbx");
	//m_Prophet = new Model("./resources/nanosuit/nanosuit.obj");
	diffuseTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest.png");
	SpecularTex = Resource::LoadTexture("./resources/HelloLightMap/WoodenChest_specular.png");
}
