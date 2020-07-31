#pragma once

#include "Painter.h"

class HelloTriangle : public Painter
{
public:

	HelloTriangle() {};

	~HelloTriangle() {};

	virtual void OnInit();

	virtual void OnRender();

	virtual void HandleInput(GLFWwindow* wnd);

	virtual void OnDeInit();

private:
	void CheckShaderCompileSuccess(GLuint shader);

	void CheckShaderLinkSucess(GLuint program);

	GLuint GetShaderProgram();

	GLuint GetShaderProgram2();

	void DrawTriganle();

	void DrawRectangle();

	void Exercise1();

	void Exercise2();

	void Exercise3();

};