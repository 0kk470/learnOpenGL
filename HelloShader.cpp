#include "HelloShader.h"

void HelloShader()
{
	/*Test1();*/
	TestUniform();
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

}