/* LearnOpenGL 0kk470*/
#pragma once

#include "Camera.h"
#include "include/Leanring/HelloTriangle.h"
#include "HelloShader.h"
#include "HelloTexture.h"
#include "HelloTransform.h"
#include "HelloCoordinate.h"
#include "HelloCamera.h"
#include "HelloLight.h"

bool IsConsoleOpen = true;

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	//if (ImGui::IsWindowHovered(ImGuiFocusedFlags_AnyWindow))
	//	return;
	auto painter = static_cast<Painter*>(glfwGetWindowUserPointer(window));
	if (painter != nullptr)
		painter->OnMouseMoveCallback(window, xpos, ypos);
}

void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{

	auto painter = static_cast<Painter*>(glfwGetWindowUserPointer(window));
	if (painter != nullptr)
		painter->OnMouseScrollCallBack(window, xoffset, yoffset);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS)
	{
		IsConsoleOpen = !IsConsoleOpen;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

Painter* CreatePainter(const char* name)
{
	if (name == "HelloTriangle")
	{
		return new HelloTriangle();
	}
	else if (name == "HelloShader")
	{
		return new HelloShader();
	}
	else if (name == "HelloTexture")
	{
		return new HelloTexture();
	}
	else if (name == "HelloTransform")
	{
		return new HelloTransform();
	}
	else if (name == "HelloCoordinate")
	{
		return new HelloCoordinate();
	}
	else if (name == "HelloCamera")
	{
		return new HelloCamera();
	}
	else if (name == "HelloLight")
	{
		return new HelloLight();
	}
	return new Painter();
}

void InitImGUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGUI_Frame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void DiposeImGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void DrawConsole()
{
	if (IsConsoleOpen)
	{
		ImGui::SetNextWindowSize(ImVec2(400, 200));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Console");
		ImGui::Text("a New Console");
		ImGui::End();
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MAC OS


	auto window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		getchar();
		return -1;
	}

	InitImGUI(window);

	Camera::GetMainCamera();
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetScrollCallback(window, OnMouseScroll);
	//glfwSetKeyCallback(window, OnKeyEvent);

	//auto painter = CreatePainter("HelloTriangle");
	//auto painter = CreatePainter("HelloShader");
	//auto painter = CreatePainter("HelloTexture");
	//auto painter = CreatePainter("HelloTransform");
	//auto painter = CreatePainter("HelloCoordinate");
	//auto painter = CreatePainter("HelloCamera");
	auto painter = CreatePainter("HelloLight");
	painter->OnInit();
	painter->OnWindowAttach(window);
	glfwSetWindowUserPointer(window, painter);

	GLfloat NextUpdateTime = 0;
	GLfloat LastGlobalTime = 0;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGUI_Frame();

		Time::GameTime = glfwGetTime();
		if (Time::GameTime < NextUpdateTime)
			continue;
		NextUpdateTime = Time::GameTime + FRAME_INTETRVAL;
		Time::deltaTime = Time::GameTime - LastGlobalTime;
		LastGlobalTime = Time::GameTime;
		//Input

		ProcessInput(window);
		painter->HandleInput(window);

		//Render
		DrawConsole();

		ImGui::Render();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		painter->OnRender();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//others
		glfwSwapBuffers(window);
	}

	painter->OnDeInit();

	DiposeImGUI();

	glfwTerminate();
	return 0;
}