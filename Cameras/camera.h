#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
float FOV = 90.0f;

class Camera{
public:
    // Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Angles
    float Yaw;
    float Pitch;

    // Camera Options
    float MovementSpeed;
    float MouseSensitivity;
    float Fov;

    // Constructor with Vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW,
           float pitch = PITCH) :
           Front(glm::vec3(0.0f, 0.0f, -1.0f)),
           MovementSpeed(SPEED),
           MouseSensitivity(SENSITIVITY),
           Fov(FOV)
           {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Constructor with Scalar Values
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ,
           float yaw, float pitch) :
           Front(glm::vec3(0.0f, 0.0f, -1.0f)),
           MovementSpeed(SPEED),
           MouseSensitivity(SENSITIVITY),
           Fov(FOV)
           {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    virtual glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void setPosition(const glm::vec3& position) {
        Position = position;
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime){
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD) {
            Position += Front * velocity;
        }
        if (direction == BACKWARD){
            Position -= Front * velocity;
        }
        if (direction == LEFT){
            Position -= Right * velocity;
        }
        if (direction == RIGHT){
            Position += Right * velocity;
        }
        if (direction == UP){
            Position += WorldUp * velocity;
        }
        if (direction == DOWN){
            Position -= WorldUp * velocity;
        }
    }

    virtual void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true){
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // Limit Vertical Mouse Movement
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset, GLFWwindow* window)
    {
        if(glfwGetKey(window, GLFW_KEY_C) != GLFW_RELEASE){
            Fov -= (float) yoffset;
        }
        if (Fov < 1.0f)
            Fov = 1.0f;
        if (Fov > 90.0f)
            Fov = 90.0f;
    }

    void ProcessZoom(int key, int action){
        if(key == GLFW_KEY_C && action == GLFW_PRESS){
            Fov = Fov / 3.0f;
        }
        if(key == GLFW_KEY_C && action == GLFW_RELEASE){
            Fov = 90.0f;
        }
    }
private:
    void updateCameraVectors(){
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif