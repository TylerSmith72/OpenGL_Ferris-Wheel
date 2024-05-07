cmake_minimum_required(VERSION 3.0)
project(Main_Project)

set(CMAKE_CXX_STANDARD 20)

# Add GLFW
add_subdirectory(Dependencies/glfw-3.4)

# Add GLAD
add_library(GLAD "Dependencies/glad/src/glad.c")
target_include_directories(GLAD PRIVATE "Dependencies/glad/include")

# Add Assimp
add_subdirectory(Dependencies/assimp-master)
include_directories(Dependencies/assimp-master/include)

include_directories(Cameras)
include_directories(Shaders)
include_directories(Meshes)

# Add executable
add_executable(Main_Project
        main.cpp
#        Shaders/4.6.shader.vs  # Add the vertex shader file
#        Shaders/4.6.shader.fs  # Add the fragment shader file
#        Shaders/old.light.shader.vs
#        Shaders/old.light.shader.fs
#        Shaders/light.cube.shader.vs
#        Shaders/light.cube.shader.fs
)

# Include GLFW, GLAD, GLM and STB_IMAGE headers
target_include_directories(Main_Project PRIVATE "Dependencies/glfw-3.4/include")
target_include_directories(Main_Project PRIVATE "Dependencies/glad/include")
target_include_directories(Main_Project PRIVATE "Dependencies/glm")
target_include_directories(Main_Project PRIVATE "Dependencies/stb")

# Copy shader files to build directory
set(SHADER_FILES
        Shaders/old.light.shader.vs
        Shaders/old.light.shader.fs
        Shaders/light.directional.shader.vs
        Shaders/light.directional.shader.fs
        Shaders/light.point.shader.vs
        Shaders/light.point.shader.fs
        Shaders/light.spot.shader.vs
        Shaders/light.spot.shader.fs
        Shaders/light.multiple.shader.fs
        Shaders/light.multiple.shader.vs
        Shaders/light.cube.shader.vs
        Shaders/light.cube.shader.fs
)

foreach(SHADER_FILE ${SHADER_FILES})
    configure_file(${SHADER_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${SHADER_FILE} COPYONLY)
endforeach()

# Copy image files to build directory
set(IMAGE_FILES
        Resources/Textures/container.jpg
        Resources/Textures/container2.png
        Resources/Textures/container2_specular.png
        Resources/Textures/awesomeface.png
)

foreach(IMAGE_FILE ${IMAGE_FILES})
    configure_file(${IMAGE_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${IMAGE_FILE} COPYONLY)
endforeach()


# Link libraries
target_link_libraries(Main_Project PRIVATE glfw GLAD assimp)
