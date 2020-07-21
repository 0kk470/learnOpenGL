#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glheader.h"

class Shader
{
public:
	GLuint Program;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	~Shader();

	void Use();

	static void CheckShaderCompileSuccess(GLuint shader);

	static void CheckShaderLinkSucess(GLuint program);

	static GLuint CreateShaderProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
};

