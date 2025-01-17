#include "GLUtils.h"
#include "Shader.h"


Shader::Shader(GLenum shaderType, const GLchar* source) {
    _id = glCreateShader(shaderType);
    glShaderSource(_id , 1, &source, NULL);
    glCompileShader(_id);
    
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::Attach(unsigned int programId) {
    glAttachShader(programId, _id);
}

void Shader::Delete() {
    if (deleted)
        return;
    glDeleteShader(_id);
    deleted = true;
}
