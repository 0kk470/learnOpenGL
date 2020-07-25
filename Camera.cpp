#include "Camera.h"

Camera* Camera::m_MainCamera = nullptr;

Camera* Camera::GetMainCamera()
{
    if (m_MainCamera == nullptr)
        m_MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    return m_MainCamera;
}

glm::mat4 Camera::GetViewMatrix()
{
    //return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    return MyOwnLookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->MovementSpeed * deltaTime;
    auto front = this->Front;
    if (!IsFly)
        front.y = 0;
    if (direction == FORWARD)
        this->Position += front * velocity;
    if (direction == BACKWARD)
        this->Position -= front * velocity;
    if (direction == LEFT)
        this->Position -= this->Right * velocity;
    if (direction == RIGHT)
        this->Position += this->Right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    this->Yaw += xoffset;
    this->Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (this->Pitch > 89.0f)
            this->Pitch = 89.0f;
        if (this->Pitch < -89.0f)
            this->Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
        this->Zoom -= yoffset * Time::deltaTime;
    if (this->Zoom <= 1.0f)
        this->Zoom = 1.0f;
    if (this->Zoom >= 45.0f)
        this->Zoom = 45.0f;
}

void Camera::SetFlyEnable(bool isEnable)
{
    IsFly = isEnable;
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}

glm::mat4 Camera::MyOwnLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 worldUp)
{
    auto lookdir = glm::normalize(from - to);

    auto right = glm::normalize(glm::cross(glm::normalize(worldUp), lookdir ) );

    auto up = glm::cross(lookdir, right);

    glm::mat4 rotation(1);
    rotation[0][0] = right.x;
    rotation[1][0] = right.y;
    rotation[2][0] = right.z;
    rotation[0][1] = up.x;
    rotation[1][1] = up.y;
    rotation[2][1] = up.z;
    rotation[0][2] = lookdir.x;
    rotation[1][2] = lookdir.y;
    rotation[2][2] = lookdir.z;

    glm::mat4 translation(1);
    translation[3][0] = -from.x;
    translation[3][1] = -from.y;
    translation[3][2] = -from.z;

    return rotation * translation;
}
