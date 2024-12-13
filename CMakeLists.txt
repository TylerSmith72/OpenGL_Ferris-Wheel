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
include_directories(Models)

# Add executable
add_executable(Main_Project
        main.cpp
)

# Include GLFW, GLAD, GLM and STB_IMAGE headers
target_include_directories(Main_Project PRIVATE "Dependencies/glfw-3.4/include")
target_include_directories(Main_Project PRIVATE "Dependencies/glad/include")
target_include_directories(Main_Project PRIVATE "Dependencies/glm")
target_include_directories(Main_Project PRIVATE "Dependencies/stb")

# Copy shader files to build directory
set(SHADER_FILES
        Shaders/light.multiple.shader.fs
        Shaders/light.multiple.shader.vs
)

foreach(SHADER_FILE ${SHADER_FILES})
    configure_file(${SHADER_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${SHADER_FILE} COPYONLY)
endforeach()

# Copy model files to build directory
file(GLOB_RECURSE MODEL_FILES "${CMAKE_SOURCE_DIR}/Resources/Models/*")
foreach(MODEL_FILE ${MODEL_FILES})
    file(RELATIVE_PATH RELATIVE_PATH "${CMAKE_SOURCE_DIR}" ${MODEL_FILE})
    configure_file(${MODEL_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${RELATIVE_PATH} COPYONLY)
endforeach()

# Link libraries
target_link_libraries(Main_Project PRIVATE glfw GLAD assimp)
