#pragma once
#include "Painter.h"

const int MAX_POINT_LIGHT_NUM = 4;

const float SCR_WIDTH = 800;

const float SCR_HEIGHT = 600;

struct DirectionLight
{
    float lightDirection[3] = { -0.2f, -1.0f, -0.3f };

    float light_ambient[3] = { 0.2f, 0.2f, 0.2f };

    float light_diffuse[3] = { 0.5f, 0.5f, 0.5f };

    float light_specular[3] = { 1.0f, 1.0f, 1.0f };

    int shininess = 32;

    bool IsOn = true;
};

struct PointLight
{
    float Position[3] = { 0.0f, 0.0f, 1.0f };

    float Ambient[3] = { 0.2f, 0.2f, 0.2f };

    float Diffuse[3] = { 0.5f, 0.5f, 0.5f };

    float Specular[3] = { 1.0f, 1.0f, 1.0f };

    float linear = 0.14f;

    float quadratic = 0.07f;

    bool isOn = true;

    PointLight(float x, float y, float z)
    {
        Position[0] = x;
        Position[1] = y;
        Position[2] = z;
    }
};

struct SpotLight
{
    float Position[3];

    float direction[3];

    float cutOff;

    float outerCutOff;

    float Ambient[3] = { 0.2f, 0.2f, 0.2f };

    float Diffuse[3] = { 0.5f, 0.5f, 0.5f };

    float Specular[3] = { 1.0f, 1.0f, 1.0f };

    float linear = 0.14f;

    float quadratic = 0.07f;

    bool isOn;
};

class HelloLightCasters : public Painter
{

public:
    void OnInit() override;

    void OnRender() override;

    void OnWindowAttach(GLFWwindow* wnd) override;

    void HandleInput(GLFWwindow* wnd) override;

    void  OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos) override;

    void  OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) override;

    void OnDeInit() override;

private:

    void Default_Update();

    void DrawLightParamWindow();

    void Default_Init();

    Shader* m_LightingObjShader, * m_LampShader;

    GLuint VBO, containerVAO, lightVAO;

    float vertices[8 * 6 * 6] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

	std::vector<glm::vec3> cubePositions =
	{
	    glm::vec3(0.0f,  0.0f,  0.0f),
	    glm::vec3(2.0f,  5.0f, -15.0f),
	    glm::vec3(-1.5f, -2.2f, -2.5f),
	    glm::vec3(-3.8f, -2.0f, -12.3f),
	    glm::vec3(2.4f, -0.4f, -3.5f),
	    glm::vec3(-1.7f,  3.0f, -7.5f),
	    glm::vec3(1.3f, -2.0f, -2.5f),
	    glm::vec3(1.5f,  2.0f, -2.5f),
	    glm::vec3(1.5f,  0.2f, -1.5f),
	    glm::vec3(-1.3f,  1.0f, -1.5f)
	};

    bool firstMouse = true;

    DirectionLight m_DirLight;

    std::vector<PointLight*> m_PointLights = std::vector<PointLight*>
    {
        new PointLight(0.7f,  0.2f,  2.0f),
        new PointLight(2.3f, -3.3f, -4.0f),
        new PointLight(-4.0f,  2.0f, -12.0f),
        new PointLight(0.0f,  0.0f, -3.0f)
    };

    SpotLight m_CameraSpotLigt;

    GLfloat lastX, lastY;

    int shininess = 32.0f;

    GLuint diffuseTex;

    GLuint SpecularTex;

    GLuint EmissionMapTex;
};


