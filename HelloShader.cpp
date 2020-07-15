#include "HelloShader.h"

void HelloShader()
{
	/*Test1();*/
	//TestUniform();
	//TestMoreProperties();
	//HelloShaderExercise1();
	//HelloShaderExercise2();
	HelloShaderExercise3();
}

void Test1()
{
	GLfloat triangle[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f, -0.5f, 0.0f,
	};
	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	Shader shader("./Shaders/Vertex/helloShader.vertex", "./Shaders/Fragment/helloShader.frag");
	shader.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void TestUniform()
{
	GLfloat triangle[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f,-0.5f,0.0f,
	0.5f, -0.5f, 0.0f,
	};
	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	Shader shader("./Shaders/Vertex/helloShader.vertex", "./Shaders/Fragment/uniform.frag");
	GLfloat timeValue = glfwGetTime();
	GLfloat greenValue = (sin(timeValue) / 2) + 0.5f;
	GLint vertexColorLocation = glGetUniformLocation(shader.Program, "vertexColor");
	shader.Use();
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void TestMoreProperties()
{
	GLfloat triangle[] = {
	//vertex			//color
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};
	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat) * 3) );
	glEnableVertexAttribArray(1);

	Shader shader("./Shaders/Vertex/MoreProperties.vertex", "./Shaders/Fragment/MoreProperties.frag");
	shader.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void HelloShaderExercise1()
{
	GLfloat triangle[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f,-0.5f,0.0f,
	0.5f, -0.5f, 0.0f,
	};
	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	Shader shader("./Shaders/Vertex/Exercise1.vertex", "./Shaders/Fragment/helloShader.frag");
	shader.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

inline float PeriodicFunc(float val)
{
	if (val > 2)
	{
		int tmp = floor(val);
		val = val - tmp + (tmp % 2 == 0 ? 0 : 1);
	}
	if (val <= 0.5f)
		return val;
	else if (val > 0.5f && val < 1.5f)
		return -val + 1;
	else
		return val - 2;
}

void HelloShaderExercise2()
{
	GLfloat triangle[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f,-0.5f,0.0f,
	0.5f, -0.5f, 0.0f,
	};
	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	Shader shader("./Shaders/Vertex/Exercise2.vertex", "./Shaders/Fragment/helloShader.frag");
	shader.Use();
	GLfloat offsetX = PeriodicFunc(glfwGetTime()); //看下pingpong效果
	GLuint offsetLocation = glGetUniformLocation(shader.Program, "offset");
	glUniform3f(offsetLocation, offsetX, 0.0f, 0.0f); 
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void HelloShaderExercise3()
{
	GLfloat triangle[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f,-0.5f,0.0f,
	0.5f, -0.5f, 0.0f,
	};
	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	Shader shader("./Shaders/Vertex/Exercise3.vertex", "./Shaders/Fragment/Exercise3.frag");
	shader.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	//为什么在三角形的左下角是黑的?
	//答:左下顶点坐标为(-0.5f, -0.5f,-0.0f) 转化为对应RGB值为(0,0,0) 为黑色
}