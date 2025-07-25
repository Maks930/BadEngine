#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <Types/Types.h>

class Camera
{
private:
    float m_fov;
    glm::vec3 m_position;

    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    glm::mat4 m_rotation;

private:
    void updateVectors();

public:
    Camera(glm::vec3 position, float fov);

    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;

    glm::vec3 getPosition();

    void setPosition(glm::vec3 position);
    void setRotation(glm::mat4 new_rotation);

    void rotate(float x, float y, float z);

    glm::mat4 getView() const;
    glm::mat4 getProjections(const WinSize& win_size) const;
};

#endif // CAMERA_H
