#ifndef FIXED_CAMERA_H
#define FIXED_CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "camera.h"

class FixedCamera : public Camera{
public:
    FixedCamera(const glm::vec3& position, const glm::vec3& lookAt)
            : Camera(position, lookAt), m_position(position), m_lookAt(lookAt) {}

    void setPosition(const glm::vec3& position) {
        m_position = position;
    }

    void setLookAt(const glm::vec3& lookAt) {
        m_lookAt = lookAt;
    }

    glm::mat4 GetViewMatrix() const override{
        return glm::lookAt(m_position, m_lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_lookAt;
};

#endif // FIXED_CAMERA_H
