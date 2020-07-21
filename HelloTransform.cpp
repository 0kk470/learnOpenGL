#include "HelloTransform.h"

void HelloTransform::OnInit()
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

	texture0 = Resource::LoadTexture("./resources/HelloTexture/wall.jpg");
	texture1 = Resource::LoadTexture("./resources/HelloTexture/awesomeface.png");
    m_PtrShader = new Shader("./Shaders/Vertex/HelloTransform/HelloTransform.vertex", "./Shaders/Fragment/HelloTexture/HelloTexture.frag");

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

	glBindVertexArray(0);
}

void HelloTransform::OnRender()
{
	TestTransform();
}

void HelloTransform::OnDeInit()
{
	glDeleteTextures(1, &texture0);
	glDeleteTextures(1, &texture1);

	delete m_PtrShader;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void HelloTransform::TestTransform()
{
	m_PtrShader->Use();

	//ApplyTransform();
	//Exercise1();
	Exercise2();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(m_PtrShader->Program, "ourTexture0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(m_PtrShader->Program, "ourTexture1"), 1);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void HelloTransform::ApplyTransform()
{
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1, 1, 1));
	//std::cout << vec.x << vec.y << vec.z << std::endl;

	glm::mat4 transform(1);
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	// Get matrix's uniform location and set matrix
	GLint transformLoc = glGetUniformLocation(m_PtrShader->Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}


void HelloTransform::Exercise1()
{
	glm::mat4 transform(1);
	transform = glm::rotate(transform, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

	// Get matrix's uniform location and set matrix
	GLint transformLoc = glGetUniformLocation(m_PtrShader->Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	/* Why does our container now spin around our screen?:
    == ===================================================
    Remember that matrix multiplication is applied in reverse. This time a translation is thus
    applied first to the container positioning it in the bottom-right corner of the screen.
    After the translation the rotation is applied to the translated container.
    
    A rotation transformation is also known as a change-of-basis transformation
    for when we dig a bit deeper into linear algebra. Since we're changing the
    basis of the container, the next resulting translations will translate the container
    based on the new basis vectors. Once the vector is slightly rotated, the vertical
    translations would also be slightly translated for example.
    
    If we would first apply rotations then they'd resolve around the rotation origin (0,0,0), but
    since the container is first translated, its rotation origin is no longer (0,0,0) making it
    looks as if its circling around the origin of the scene.
    
    If you had trouble visualizing this or figuring it out, don't worry. If you
    experiment with transformations you'll soon get the grasp of it; all it takes
    is practice and experience.
    */
}

void HelloTransform::Exercise2()
{
	glm::mat4 transform(1);
	auto fScale = abs( glm::sin(glfwGetTime()) );
	transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
	transform = glm::rotate(transform, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(fScale, fScale, fScale));

	// Get matrix's uniform location and set matrix
	GLint transformLoc = glGetUniformLocation(m_PtrShader->Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}
