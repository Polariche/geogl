#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

static std::string load_text(const char* path) {
    std::ifstream file_stream(path);

    if (!file_stream.is_open()) {
        printf("ERROR OPENING FILE! %s\n", path);
        return nullptr;
    }

    std::string content(
        (std::istreambuf_iterator<char>(file_stream)),
        std::istreambuf_iterator<char>()
    );

    return content;
}