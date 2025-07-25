#include "camera.h"

void Camera::updateVectors()
{
    m_front     = glm::vec3(m_rotation * glm::vec4(0,0,-1,1));
    m_right     = glm::vec3(m_rotation * glm::vec4(1,0,0,1));
    m_up        = glm::vec3(m_rotation * glm::vec4(0,1,0,1));

}

Camera::Camera(glm::vec3 position, float fov):
    m_position(position), m_fov(fov), m_rotation(1.0f)
{
    updateVectors();
}

glm::vec3 Camera::getPosition()
{
    return m_position;
}

void Camera::setPosition(glm::vec3 position)
{
    m_position = position;
    updateVectors();
}

void Camera::setRotation(glm::mat4 new_rotation)
{
    m_rotation = new_rotation;
}

void Camera::rotate(float x, float y, float z)
{
    m_rotation = glm::rotate(m_rotation, z, glm::vec3(0,0,1));
    m_rotation = glm::rotate(m_rotation, y, glm::vec3(0,1,0));
    m_rotation = glm::rotate(m_rotation, x, glm::vec3(1,0,0));
    updateVectors();
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjections(const WinSize &win_size) const
{
    float aspect = static_cast<float>(win_size.width) / static_cast<float>(win_size.height);
    return glm::perspective(m_fov, aspect, 0.1f, 100.0f);
}

glm::vec3 Camera::getFront() const
{
    return m_front;
}

glm::vec3 Camera::getUp() const
{
    return m_up;
}

glm::vec3 Camera::getRight() const
{
    return m_right;
}
