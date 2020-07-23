#include "HelloCoordinate.h"


void HelloCoordinate::OnInit()
{
    glEnable(GL_DEPTH_TEST);

    m_PtrShader = new Shader("./Shaders/Vertex/HelloCoordinate/HelloCoordinate.vertex", "./Shaders/Fragment/HelloCoordinate/HelloCoordinate.frag");

    // Set up vertex data (and buffer(s)) and attribute pointers

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLvoid*)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    texture0 = Resource::LoadTexture("./resources/HelloTexture/wall.jpg",GL_REPEAT, GL_LINEAR);
    texture1 = Resource::LoadTexture("./resources/HelloTexture/awesomeface.png", GL_REPEAT, GL_LINEAR);
}


const GLuint WIDTH = 800, HEIGHT = 600;

void HelloCoordinate::OnRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_PtrShader->Use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glUniform1i(glGetUniformLocation(m_PtrShader->Program, "ourTexture0"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(m_PtrShader->Program, "ourTexture1"), 1);

    glm::mat4 view(1);
    glm::mat4 projection(1);
    //view = glm::translate(view, glm::vec3(0, 0, -3));
    //projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

    //Exercise2
    view = glm::translate(view, ViewMat3);

    //Exercise1
    projection = glm::perspective(FOV, AspectRatio, 0.1f, 100.0f);

    GLuint modelLoc = glGetUniformLocation(m_PtrShader->Program, "model");
    GLint viewLoc = glGetUniformLocation(m_PtrShader->Program, "view");
    GLint projLoc = glGetUniformLocation(m_PtrShader->Program, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);

    for (auto i = 0; i < 10; ++i)
    {
        glm::mat4 model(1);
        model = glm::translate(model, cubePositions[i]);
        //GLfloat angle = 20 * i;
        //model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        Exercise3(i, model);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);

}

void HelloCoordinate::OnDeInit()
{
    delete m_PtrShader;
    m_PtrShader = nullptr;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void HelloCoordinate::HandleInput(GLFWwindow* wnd)
{
    Exercise1(wnd);
    Exercise2(wnd);
}

void HelloCoordinate::Exercise1(GLFWwindow* wnd)
{
    if(glfwGetKey(wnd, GLFW_KEY_U))
    {
        FOV -= FOVSpeed * Time::deltaTime;
    }
    else if(glfwGetKey(wnd, GLFW_KEY_I))
    {
        FOV += FOVSpeed * Time::deltaTime;
    }

    if (glfwGetKey(wnd, GLFW_KEY_O))
    {
        AspectRatio -= AspectRatioSpeed * Time::deltaTime;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_P))
    {
        AspectRatio += AspectRatioSpeed * Time::deltaTime;
    }
    FOV = fmax(fmin(FOV, 60), 45);
    AspectRatio = fmax(fmin(AspectRatio, 2), 1);
}

void HelloCoordinate::Exercise2(GLFWwindow* wnd)
{
    GLfloat movement = MoveSpeed * Time::deltaTime;
    if (glfwGetKey(wnd, GLFW_KEY_W))
    {
        ViewMat3.z += movement;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_S))
    {
        ViewMat3.z -= movement;
    }
    if (glfwGetKey(wnd, GLFW_KEY_A))
    {
        ViewMat3.x += movement;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_D))
    {
        ViewMat3.x -= movement;
    }
    if (glfwGetKey(wnd, GLFW_KEY_Z))
    {
        ViewMat3.y -= movement;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_C))
    {
        ViewMat3.y += movement;
    }
}

void HelloCoordinate::Exercise3(int i, glm::mat4& model)
{
    float angle = 29 * i;
    if (i % 3 == 0)  
        angle = glfwGetTime() * 25.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
}
