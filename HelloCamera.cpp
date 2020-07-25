#include "HelloCamera.h"


void HelloCamera::OnInit()
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


    texture0 = Resource::LoadTexture("./resources/HelloTexture/wall.jpg", GL_REPEAT, GL_LINEAR);
    texture1 = Resource::LoadTexture("./resources/HelloTexture/awesomeface.png", GL_REPEAT, GL_LINEAR);

    //Exercise 1
    Camera::GetMainCamera()->SetFlyEnable(false);
}


const GLuint WIDTH = 800, HEIGHT = 600;

void HelloCamera::OnRender()
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

    view = Camera::GetMainCamera()->GetViewMatrix();

    projection = glm::perspective(Camera::GetMainCamera()->Zoom, AspectRatio, 0.1f, 100.0f);

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
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);

}

void HelloCamera::OnDeInit()
{
    delete m_PtrShader;
    m_PtrShader = nullptr;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void HelloCamera::HandleInput(GLFWwindow* wnd)
{
    //Exercise1(wnd);
    GLfloat deltaTime = Time::deltaTime;
    auto mainCamera = Camera::GetMainCamera();
    if (glfwGetKey(wnd, GLFW_KEY_W))
    {
        mainCamera->ProcessKeyboard(FORWARD, deltaTime);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_S))
    {
        mainCamera->ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(wnd, GLFW_KEY_A))
    {
        mainCamera->ProcessKeyboard(LEFT, deltaTime);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_D))
    {
        mainCamera->ProcessKeyboard(RIGHT, deltaTime);
    }
}

void HelloCamera::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	Camera::GetMainCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void HelloCamera::OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera::GetMainCamera()->ProcessMouseScroll(yoffset);
}
