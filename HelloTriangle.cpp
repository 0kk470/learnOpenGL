#include "include/Leanring/HelloTriangle.h"

void CheckShaderCompileSuccess(GLuint shader)
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

void CheckShaderLinkSucess(GLuint program)
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

GLuint GetShaderProgram()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

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

GLuint GetShaderProgram2()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"  FragColor = vec4(1.0f, 240f / 255f, 69f / 255f, 1.0f);\n"
		"}\0";

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


void DrawTriganle()
{
	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	//复制顶点数组到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glUseProgram(GetShaderProgram());

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void DrawRectangle()
{
	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	GLuint indices[] = {
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

		//复制顶点数组到缓冲中供OpenGL使用
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//索引数组
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//设置顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glUseProgram(GetShaderProgram());

	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void Exercise1()
{
	GLfloat vertices[] = {
		-1.0f ,0.0f, 0.0f,
		-0.5f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
		1.0f ,0.0f, 0.0f,
		0.5f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(GLfloat) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glUseProgram(GetShaderProgram());

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Exercise2()
{
	GLfloat firstTriangle[] = {
	-0.9f, -0.5f, 0.0f,  // Left 
	-0.0f, -0.5f, 0.0f,  // Right
	-0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat secondTriangle[] = {
		 0.0f, -0.5f, 0.0f,  // Left
		 0.9f, -0.5f, 0.0f,  // Right
		 0.45f, 0.5f, 0.0f   // Top 
	};

	GLuint VBO[2];
	glGenBuffers(2, VBO);

	GLuint VAO[2];
	glGenVertexArrays(2, VAO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glUseProgram(GetShaderProgram());
	
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
}

void Exercise3()
{
	GLfloat firstTriangle[] = {
	-0.9f, -0.5f, 0.0f,  // Left 
	-0.0f, -0.5f, 0.0f,  // Right
	-0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat secondTriangle[] = {
		 0.0f, -0.5f, 0.0f,  // Left
		 0.9f, -0.5f, 0.0f,  // Right
		 0.45f, 0.5f, 0.0f   // Top 
	};

	GLuint VBO[2];
	glGenBuffers(2, VBO);

	GLuint VAO[2];
	glGenVertexArrays(2, VAO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glUseProgram(GetShaderProgram());
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(GetShaderProgram2());
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
}

void HelloTriangle()
{

	//DrawTriganle();
	//DrawRectangle();
	//Exercise1();
	//Exercise2();
	Exercise3();
}