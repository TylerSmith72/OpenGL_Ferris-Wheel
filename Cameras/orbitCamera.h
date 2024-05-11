#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class OrbitCamera : public Camera{
public:
    OrbitCamera(const glm::vec3& center, float radius)
            : Camera(center + glm::vec3(0.0f, 0.0f, radius), center),
            m_center(center), m_radius(radius), m_angle(0.0f) {}

    void lookAtCenter() {
        m_lookAt = m_center;
    }

    void moveAroundCenter(float deltaAngle) {
        m_angle += deltaAngle;
        float x = m_center.x + m_radius * cos(m_angle);
        float z = m_center.z + m_radius * sin(m_angle);
        m_position = glm::vec3(x, m_center.y, z);
    }

    glm::mat4 GetViewMatrix() const override{
        return glm::lookAt(m_position, m_lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void moveUp(float deltaHeight) {
        m_center.y += deltaHeight;
    }

    void moveDown(float deltaHeight) {
        m_center.y -= deltaHeight;
    }

    void increaseRadius(float deltaRadius) {
        m_radius += deltaRadius;
    }

    void decreaseRadius(float deltaRadius) {
        m_radius -= deltaRadius;
        if (m_radius < 1.0f) {
            m_radius = 1.0f; // Ensure radius is non-negative
        }
    }

private:
    glm::vec3 m_center;
    glm::vec3 m_position;
    glm::vec3 m_lookAt;
    float m_radius;
    float m_angle;
};

#endif // ORBIT_CAMERA_H
