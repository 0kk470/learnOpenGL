#include "Shader.h"

using std::string;
using std::ifstream;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	
	vShaderFile.exceptions(ifstream::badbit);
	fShaderFile.exceptions(ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "ERROR: SHADER :: FILE_NOT_SUCCESSFULLY_READ " << std :: endl;
	}

	Program = CreateShaderProgram(vertexCode.c_str(), fragmentCode.c_str());
}

Shader::~Shader()
{
	glDeleteProgram(Program);
}

void Shader::Use()
{
	glUseProgram(Program);
}

void Shader::CheckShaderCompileSuccess(GLuint shader)
{
	int success;
	char logstr[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, logstr);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << logstr << std::endl;
	}
}

void Shader::CheckShaderLinkSucess(GLuint program)
{
	int success;
	char logstr[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, logstr);
		std::cout << "ERROR::PROGARAM::LINK::COMPILATION_FAILED\n" << logstr << std::endl;
	}
}

GLuint Shader::CreateShaderProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		CheckShaderCompileSuccess(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		CheckShaderCompileSuccess(fragmentShader);

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		CheckShaderLinkSucess(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
}
