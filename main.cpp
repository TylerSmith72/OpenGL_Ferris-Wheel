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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void zoom_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// Settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Cameras
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
FixedCamera fixedCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));
OrbitCamera orbitCamera(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f);

Camera* currentCamera = &camera;  // Start with the fixed camera

float lastX = SCR_WIDTH  / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool key0Pressed = false;

float cameraSpeed = 5.0f;
float radiusSpeed = 5.0f;
const float sensitivity = 0.5f;

// Torch
bool spotLightOn = false;
bool torchKeyPress = false;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window in OS
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, zoom_callback);

    // Disable Cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    //Shader ourShader("Shaders/light.model_loading.vs", "Shaders/light.model_loading.fs");
    Shader ourShader("Shaders/light.multiple.shader.vs", "Shaders/light.multiple.shader.fs");
    Model ourModel("Resources/Models/backpack/backpack.obj");
    //Model ourModel("Resources/Models/backpack/backpack.obj");

    // Set light properties
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f); // white light


// Pass light properties to shader
    ourShader.use(); // don't forget to activate the shader before setting uniforms!
    ourShader.setVec3("pointLights[0].position", lightPos);
    ourShader.setVec3("pointLights[0].ambient", 0.1f * lightColor);
    ourShader.setVec3("pointLights[0].diffuse", 0.8f * lightColor);
    ourShader.setVec3("pointLights[0].specular", 1.0f * lightColor);
    ourShader.setFloat("pointLights[0].constant", 1.0f);
    ourShader.setFloat("pointLights[0].linear", 0.09f);
    ourShader.setFloat("pointLights[0].quadratic", 0.032f);


    // Main Loop
    while(!glfwWindowShouldClose(window))
    {
        // Per-Frame Logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set clear colour
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear to colour previously set

        // Start Shader
        ourShader.use();
        ourShader.setVec3("viewPos", currentCamera->Position);
        ourShader.setFloat("material.shininess", 32.0f);


        // View and Projection Transformation
        glm::mat4 projection = glm::perspective(glm::radians(currentCamera->Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = currentCamera->GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // Render Loaded Model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        // LIGHTS //

        // Directional
        ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        ourShader.setVec3("dirLight.ambient", 0.8f, 0.8f, 0.8f);
        ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        // Spotlight (Torch)
        ourShader.setVec3("spotLight.position", currentCamera->Position);
        ourShader.setVec3("spotLight.direction", currentCamera->Front);
        ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        ourShader.setFloat("spotLight.constant", 1.0f);
        ourShader.setFloat("spotLight.linear", 0.09f);
        ourShader.setFloat("spotLight.quadratic", 0.032f);
        if(spotLightOn){

            ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(25.0f)));
            ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(30.0f)));
        }
        else{
            ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(0.0f)));
            ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(0.0f)));
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

    // Switching Cameras
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        key0Pressed = true;
    } else if (key0Pressed) {
        if (currentCamera == &camera) {
            currentCamera = &fixedCamera;
        } else if (currentCamera == &fixedCamera) {
            currentCamera = &orbitCamera;
        } else {
            currentCamera = &camera;
        }

        key0Pressed = false;
    }

    if(currentCamera == &camera){
        // Camera: Move
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            currentCamera->ProcessKeyboard(FORWARD, deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            currentCamera->ProcessKeyboard(BACKWARD, deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            currentCamera->ProcessKeyboard(LEFT, deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            currentCamera->ProcessKeyboard(RIGHT, deltaTime);
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
            currentCamera->ProcessKeyboard(UP, deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
            currentCamera->ProcessKeyboard(DOWN, deltaTime);
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    if(currentCamera == &camera){
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


