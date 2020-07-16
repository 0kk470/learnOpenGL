#include "HelloTexture.h"

void HelloTexture(GLFWwindow* window)
{
	//TextureTest();
	//TextureExercise1();
	//TextureExercise2();
	//TextureExercise3();
	TextureExercise4(window);
}

GLuint LoadTexture(const GLchar* path, GLint wrapMode, GLint MagFilterMode , GLint MinFilterMode)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//float borderColor[] = { 1.0f, 0.6f, 0.6f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilterMode);

	int width, height;
	auto image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}

void TextureTest()
{
	GLfloat vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
	};

	GLuint texture0 = LoadTexture("./resources/HelloTexture/wall.jpg");
	GLuint texture1 = LoadTexture("./resources/HelloTexture/awesomeface.png");

	Shader shader("./Shaders/Vertex/HelloTexture/HelloTexture.vertex", "./Shaders/Fragment/HelloTexture/HelloTexture.frag");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);

	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture0") ,0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 1);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void TextureExercise1()
{
	GLfloat vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
	};

	GLuint texture0 = LoadTexture("./resources/HelloTexture/wall.jpg");
	GLuint texture1 = LoadTexture("./resources/HelloTexture/awesomeface.png");

	Shader shader("./Shaders/Vertex/HelloTexture/HelloTexture.vertex", "./Shaders/Fragment/HelloTexture/Exercise1.frag");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);

	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 1);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void TextureExercise2()
{
	GLfloat vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // 左上
	};//对比Exercise1产生的变化

	GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
	};

	GLuint texture0 = LoadTexture("./resources/HelloTexture/wall.jpg",GL_CLAMP_TO_EDGE, GL_NEAREST);  //对比Exercise1产生的变化
	GLuint texture1 = LoadTexture("./resources/HelloTexture/awesomeface.png", GL_REPEAT, GL_NEAREST); //对比Exercise1产生的变化

	Shader shader("./Shaders/Vertex/HelloTexture/HelloTexture.vertex", "./Shaders/Fragment/HelloTexture/HelloTexture.frag"); //对比Exercise1产生的变化

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);

	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 1);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void TextureExercise3()
{
	GLfloat vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f    // 左上
	};

	GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
	};//对比Exercise1产生的变化

	GLuint texture0 = LoadTexture("./resources/HelloTexture/wall.jpg", GL_REPEAT, GL_NEAREST);//对比Exercise1产生的变化
	GLuint texture1 = LoadTexture("./resources/HelloTexture/awesomeface.png", GL_REPEAT, GL_NEAREST);//对比Exercise1产生的变化

	Shader shader("./Shaders/Vertex/HelloTexture/HelloTexture.vertex", "./Shaders/Fragment/HelloTexture/HelloTexture.frag");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);

	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 1);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

Shader* sd;
void TextureExercise4(GLFWwindow* window)
{
	GLfloat vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
	};

	GLuint texture0 = LoadTexture("./resources/HelloTexture/wall.jpg");
	GLuint texture1 = LoadTexture("./resources/HelloTexture/awesomeface.png");

	if(sd == nullptr)
	 sd = new Shader("./Shaders/Vertex/HelloTexture/HelloTexture.vertex", "./Shaders/Fragment/HelloTexture/Exercise4.frag");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);

	if (sd != nullptr)
		sd->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(sd->Program, "ourTexture0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(sd->Program, "ourTexture1"), 1);

	UpdateMixValue(window, sd->Program);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

//GLfloat val = 0.2f;

void UpdateMixValue(GLFWwindow* wnd, GLuint shaderProgram)
{
	auto location = glGetUniformLocation(shaderProgram, "mixValue");
	auto val = 0.0f;
	glGetUniformfv(shaderProgram, location, &val);
	if (glfwGetKey(wnd, GLFW_KEY_UP) || glfwGetKey(wnd, GLFW_KEY_W))
	{
		val -= 0.05f;
	}
	else if (glfwGetKey(wnd, GLFW_KEY_DOWN) || glfwGetKey(wnd, GLFW_KEY_S))
	{
		val += 0.05f;
	}
	val = std::fmin(1, std::fmax(val, 0));
	glUniform1f(glGetUniformLocation(shaderProgram, "mixValue"), val);
}


