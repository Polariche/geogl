cmake_minimum_required(VERSION 3.16.3)
project(geogl)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW 2.1 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(geogl
        src/Common/GL/GLApp.cpp
        src/Common/GL/Shader.cpp
        src/Scenes/tutorials/tutorial_02.cpp
)
target_link_libraries(geogl
        glfw
        OpenGL
        GLEW
        glm::glm
)