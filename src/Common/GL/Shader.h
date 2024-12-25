#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader {
private:
    unsigned int _id;
    bool deleted = 0;

public:
    Shader(GLenum shaderType, const GLchar* source);
    ~Shader();

    void Attach(unsigned int programId);
    void Delete();
};