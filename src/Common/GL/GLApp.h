#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BufferObject.h"
#include "Shader.h"

class GLApp {

public:
    ~GLApp(); // Declaration of virtual destructor

public:
    void Run();

public:
    virtual bool Initialize() = 0;

protected:
    virtual void OnResize() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    virtual void OnMouseDown(int button, double xpos, double ypos) = 0;
    virtual void OnMouseUp(int button, double xpos, double ypos) = 0;
    virtual void OnMouseMove(double xpos, double ypos) = 0;
    
//     virtual void OnKeyDown() {}
//     virtual void OnKeyUp() {}

protected:
    bool InitOpenGL();
    bool InitShaders();
    bool InitCallbacks();

public:
    inline GLFWwindow* GetWindow() { return window; }

protected:
    GLFWwindow* window;
    int width = 640;
    int height = 640;


private:
    unsigned int shaderProgram;
    Shader* vertexShader;
    Shader* geometryShader;
    Shader* fragmentShader;

};