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


void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
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

	Camera::GetMainCamera();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetScrollCallback(window, OnMouseScroll);

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

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		painter->OnRender();
		//others

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	painter->OnDeInit();

	glfwTerminate();
	return 0;
}