#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "shader_s.h"
#include "camera.h"
#include "fixedCamera.h"
#include "orbitCamera.h"
#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool isInsideBox(glm::vec3 position, glm::vec3 boxMin, glm::vec3 boxMax);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void zoom_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);
void processPositions();
unsigned int loadTexture(const char *path);

// Settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Cameras
Camera camera(glm::vec3(0.0f, 10.0f, 0.0f));
FixedCamera fixedCamera(glm::vec3(10.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
Camera rideFreeCamera(glm::vec3(0.0f, 18.0f, -12.0f));
OrbitCamera orbitCamera(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f);

Camera* currentCamera = &camera;  // Start with the fixed camera

float lastX = SCR_WIDTH  / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool key0Pressed = false;

float cameraSpeed = 5.0f;
float radiusSpeed = 5.0f;
const float sensitivity = 0.5f;

glm::vec3 boxMin = glm::vec3(-15.5f, -3, -20.5);
glm::vec3 boxMax = glm::vec3(15.5f, 3, 20.5);

// Torch
bool spotLightOn = false;
bool torchKeyPress = false;

// Ride Settings
float rideSpeed = 5.0f;
bool rideStart = false;
bool keyEPressed = false;
float rideRadius = 12.0f;
float rideHeight = 18.0f;
glm::vec3 rideCenter = glm::vec3(0.0f, 18.0f, 0.0f);
float theta = 0.0f;
float rideFixedCamAngle = 0.0f;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window in OS
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ferris Wheel", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, zoom_callback);

    // GL Settings
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Shader
    Shader ourShader("Shaders/light.multiple.shader.vs", "Shaders/light.multiple.shader.fs");

    // LOAD SCENE //

    // Extra Models
    Model ourModel("Resources/Models/backpack/backpack.obj");
    ourModel.setRotation(glm::vec3(-90.0f, 20.0f, 0.0f));
    ourModel.setPosition(glm::vec3(-9.0f, 3.2f, 14.0f));


    // Ride
    Model base("Resources/Models/ferris_wheel_base/ferris_wheel_base.obj");
    Model wheel("Resources/Models/ferris_wheel/ferris_wheel.obj");
    base.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    wheel.setPosition(glm::vec3(0.0f, 18.0f, 0.0f));
    wheel.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));


    // Carts
    std::vector<glm::vec3> cartPos = {
            glm::vec3(0.0f, 5.0f, 0.0f),
            glm::vec3(0.0f, 17.0f, -12.0f),
            glm::vec3(0.0f, 29.0f, 0.0f),
            glm::vec3(0.0f, 17.0f, 12.0f)
    };
    std::vector<float> cartAngles = {
            0.0f,
            90.0f,
            180.0f,
            270.0f
    };
    std::vector<Model> carts = {
            Model ("Resources/Models/ferris_wheel_cart/Crate1.obj"),
            Model ("Resources/Models/ferris_wheel_cart/Crate1.obj"),
            Model ("Resources/Models/ferris_wheel_cart/Crate1.obj"),
            Model ("Resources/Models/ferris_wheel_cart/Crate1.obj")
    };
    for (int i = 0; i < cartPos.size(); i++){
        carts[i].setPosition(cartPos[i]);
    }

    // Containers
    std::vector<glm::vec3> containerPos = {
        glm::vec3(-12.0f, 2.8f, 16.0f),
        glm::vec3(-12.0f, 2.8f, 14.0f),
        glm::vec3(-11.0f, 2.8f, 10.5f),
        glm::vec3(-9.5f, 2.8f, 17.0f),
        glm::vec3(-12.0f, 4.8f, 16.0f),
    };
    std::vector<glm::vec3> containerRot = {
            glm::vec3(0.00f, 0.0f, 0.0f),
            glm::vec3(0.00f, 0.0f, 0.0f),
            glm::vec3(0.00f, 30.0f, 0.0f),
            glm::vec3(0.00f, -15.0f, 0.0f),
            glm::vec3(0.00f, -30.0f, 0.0f),
    };
    std::vector<Model> containers = {
            Model ("Resources/Models/container/Crate1.obj"),
            Model ("Resources/Models/container/Crate1.obj"),
            Model ("Resources/Models/container/Crate1.obj"),
            Model ("Resources/Models/container/Crate1.obj"),
            Model ("Resources/Models/container/Crate1.obj"),
    };
    for(int i = 0; i < containerPos.size(); i++){
        containers[i].setPosition(containerPos[i]);
        containers[i].setRotation(containerRot[i]);
    }

    glm::vec3 lightColor(1.0f, 1.0f, 1.0f); // white light

    // Point Lights
    ourShader.use();
    for (int i = 0; i < cartPos.size(); i++) {
        std::string base = "pointLights[" + std::to_string(i) + "]";
        ourShader.setVec3(base + ".position", cartPos[i]);
        ourShader.setVec3(base + ".ambient", 0.1f * lightColor);
        ourShader.setVec3(base + ".diffuse", 0.8f * lightColor);
        ourShader.setVec3(base + ".specular", 1.0f * lightColor);
        ourShader.setFloat(base + ".constant", 1.0f);
        ourShader.setFloat(base + ".linear", 0.09f);
        ourShader.setFloat(base + ".quadratic", 0.032f);
    }

    // Camera Settings
    orbitCamera.setRadius(30.0f);
    orbitCamera.setHeight(30.0f);

    // Main Loop
    while(!glfwWindowShouldClose(window))
    {
        // Per-Frame Logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);
        processPositions();

        // Background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set clear colour
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear to colour previously set

        // Start Shader
        ourShader.use();
        ourShader.setVec3("viewPos", currentCamera->Position);
        ourShader.setFloat("material.shininess", 64.0f);


        // View and Projection Transformation
        glm::mat4 projection = glm::perspective(glm::radians(currentCamera->Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = currentCamera->GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        if(rideStart){
            wheel.rotate(glm::vec3(rideSpeed * deltaTime, 0.0f, 0.0f));
        }

        base.Draw(ourShader);
        wheel.Draw(ourShader);
        ourModel.Draw(ourShader);

        for(int i = 0; i < containerPos.size(); i++){
            containers[i].Draw(ourShader);
        }

        // Move Carts
        for (int i = 0; i < cartPos.size(); i++){
            std::string base = "pointLights[" + std::to_string(i) + "]";
            if(rideStart){
                cartAngles[i] += deltaTime * rideSpeed;

                glm::vec3 cartPosition;
                cartPosition.x = 0.0f;
                cartPosition.y = (rideCenter.y - 1.0f) + rideRadius * sin(glm::radians(-cartAngles[i]));
                cartPosition.z = rideCenter.z + rideRadius * cos(glm::radians(-cartAngles[i]));

                ourShader.setVec3(base + ".position", cartPosition);

                carts[i].setPosition(cartPosition);
            }

            carts[i].Draw(ourShader);
        }

        // LIGHTS //

        // Directional
        ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        ourShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
        ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        // Spotlight (Ride)
        ourShader.setVec3("spotLightRide.position", glm::vec3(15.0f, 10.0f, 0.0f));
        ourShader.setVec3("spotLightRide.direction", glm::vec3(-0.5f, -1.0f, 0.0f));
        ourShader.setVec3("spotLightRide.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLightRide.diffuse", 4.0f, 4.0f, 4.0f);
        ourShader.setVec3("spotLightRide.specular", 0.5f, 0.5f, 0.5f);
        ourShader.setFloat("spotLightRide.constant", 1.0f);
        ourShader.setFloat("spotLightRide.linear", 0.09f);
        ourShader.setFloat("spotLightRide.quadratic", 0.032f);
        ourShader.setFloat("spotLightRide.cutOff", glm::cos(glm::radians(15.0f)));
        ourShader.setFloat("spotLightRide.outerCutOff", glm::cos(glm::radians(20.0f)));

        // Spotlight (Torch)
        ourShader.setVec3("spotLightTorch.position", currentCamera->Position);
        ourShader.setVec3("spotLightTorch.direction", currentCamera->Front);
        ourShader.setVec3("spotLightTorch.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLightTorch.diffuse", 4.0f, 4.0f, 4.0f);
        ourShader.setVec3("spotLightTorch.specular", 0.5f, 0.5f, 0.5f);
        ourShader.setFloat("spotLightTorch.constant", 1.0f);
        ourShader.setFloat("spotLightTorch.linear", 0.09f);
        ourShader.setFloat("spotLightTorch.quadratic", 0.032f);
        if(spotLightOn){

            ourShader.setFloat("spotLightTorch.cutOff", glm::cos(glm::radians(25.0f)));
            ourShader.setFloat("spotLightTorch.outerCutOff", glm::cos(glm::radians(30.0f)));
        }
        else{
            ourShader.setFloat("spotLightTorch.cutOff", glm::cos(glm::radians(0.0f)));
            ourShader.setFloat("spotLightTorch.outerCutOff", glm::cos(glm::radians(0.0f)));
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate(); // Properly cleans up resources
    return 0;
}

void processInput(GLFWwindow *window)
{
    // Exit
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // Start-Stop Ride
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        if(!keyEPressed)
        {
            rideStart = !rideStart;
            keyEPressed = true;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
    {
        keyEPressed = false;
    }

    // Switching Cameras
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        key0Pressed = true;
    } else if (key0Pressed) {
        if (currentCamera == &camera) {
            currentCamera = &fixedCamera;
        } else if (currentCamera == &fixedCamera) {
            currentCamera = &rideFreeCamera;
        } else if (currentCamera == &rideFreeCamera) {
            currentCamera = &orbitCamera;
        } else {
            currentCamera = &camera;
        }

        key0Pressed = false;
    }

    if(currentCamera == &camera){
        // Camera: Move
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            glm::vec3 newPosition = currentCamera->Position + currentCamera->Front * deltaTime * currentCamera->MovementSpeed;
            if (!isInsideBox(newPosition, boxMin, boxMax)) {
                currentCamera->ProcessKeyboard(FORWARD, deltaTime);
            }
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            glm::vec3 newPosition = currentCamera->Position - currentCamera->Front * deltaTime * currentCamera->MovementSpeed;
            if (!isInsideBox(newPosition, boxMin, boxMax)) {
                currentCamera->ProcessKeyboard(BACKWARD, deltaTime);
            }
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            glm::vec3 newPosition = currentCamera->Position - currentCamera->Right * deltaTime * currentCamera->MovementSpeed;
            if (!isInsideBox(newPosition, boxMin, boxMax)) {
                currentCamera->ProcessKeyboard(LEFT, deltaTime);
            }
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            glm::vec3 newPosition = currentCamera->Position + currentCamera->Right * deltaTime * currentCamera->MovementSpeed;
            if (!isInsideBox(newPosition, boxMin, boxMax)) {
                currentCamera->ProcessKeyboard(RIGHT, deltaTime);
            }
        }

        // Sprinting
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
            currentCamera->MovementSpeed = cameraSpeed * 2;
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
            currentCamera->MovementSpeed = cameraSpeed;
        }

        // Camera: Up - Down
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            glm::vec3 newPosition = currentCamera->Position + currentCamera->Up * deltaTime * currentCamera->MovementSpeed;
            if (!isInsideBox(newPosition, boxMin, boxMax)) {
                currentCamera->ProcessKeyboard(UP, deltaTime);
            }
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
            glm::vec3 newPosition = currentCamera->Position - currentCamera->Up * deltaTime * currentCamera->MovementSpeed;
            if (!isInsideBox(newPosition, boxMin, boxMax)) {
                currentCamera->ProcessKeyboard(DOWN, deltaTime);
            }
        }

        // Torch
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        {
            if(!torchKeyPress)
            {
                spotLightOn = !spotLightOn;
                torchKeyPress = true;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
        {
            torchKeyPress = false;
        }
    }

    if(currentCamera == &orbitCamera){
        OrbitCamera* orbitPtr = dynamic_cast<OrbitCamera*>(currentCamera);
        if (orbitPtr) {
            if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ){
                orbitPtr->moveAroundCenter(deltaTime * 2);
            }

            if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE ){
                orbitPtr->moveAroundCenter(deltaTime);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            orbitCamera.moveUp(deltaTime * cameraSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            orbitCamera.moveDown(deltaTime * cameraSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            orbitCamera.increaseRadius(deltaTime * radiusSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            orbitCamera.decreaseRadius(deltaTime * radiusSpeed);
        }
    }
}

void processPositions(){
    if(rideStart){
        // Ground Fixed Camera - LookAt
        FixedCamera* fixedPtr = dynamic_cast<FixedCamera*>(&fixedCamera);

        if(fixedPtr){
            theta += deltaTime * rideSpeed;

            glm::vec3 lookAt;
            lookAt.x = 0.0f;
            lookAt.y = (rideCenter.y - 1.0) + rideRadius * sin(glm::radians(-theta));
            lookAt.z = rideCenter.z + rideRadius * cos(glm::radians(-theta));

            fixedPtr->setLookAt(lookAt);
        }

        // Ride Fixed Camera - Position
        rideFixedCamAngle += deltaTime * rideSpeed;

        glm::vec3 cartCamPosition;
        cartCamPosition.x = 0.0f;
        cartCamPosition.y = (rideCenter.y - 1.0f) + rideRadius * sin(glm::radians(-rideFixedCamAngle));
        cartCamPosition.z = rideCenter.z + rideRadius * cos(glm::radians(-rideFixedCamAngle));

        rideFreeCamera.setPosition(cartCamPosition);
    }
}

bool isInsideBox(glm::vec3 position, glm::vec3 boxMin, glm::vec3 boxMax) {
    return position.x >= boxMin.x && position.y >= boxMin.y && position.z >= boxMin.z
           && position.x <= boxMax.x && position.y <= boxMax.y && position.z <= boxMax.z;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    if(currentCamera == &camera || currentCamera == &rideFreeCamera){
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        currentCamera->ProcessMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    currentCamera->ProcessMouseScroll(static_cast<float>(yoffset), window);
}

void zoom_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    currentCamera->ProcessZoom(key, action);
}


