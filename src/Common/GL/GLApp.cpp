
#include "GLUtils.h"
#include "GLApp.h"

GLApp::~GLApp() {
} 

void GLApp::Run() {
    while (!glfwWindowShouldClose(window))
    {   
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Update();
        Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool GLApp::InitOpenGL() {

    if (!glfwInit())
        return false;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(width, height, "OpenGL App", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLenum result = glewInit();

    glEnable(GL_PROGRAM_POINT_SIZE);

    return true;
}

bool GLApp::InitShaders(const char*  vertexPath, const char* fragPath) {
    shaderProgram = glCreateProgram();

    std::string vertexShaderSource = load_text(vertexPath);
    if (!vertexShaderSource.empty()) {
        vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
        vertexShader->Attach(shaderProgram);
        vertexShader->Delete();
    }

    std::string fragmentShaderSource = load_text(fragPath);
    if (!fragmentShaderSource.empty()) {
        fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
        fragmentShader->Attach(shaderProgram);
        fragmentShader->Delete();
    }

    glLinkProgram(shaderProgram);
    

    return true;
}

bool GLApp::InitCallbacks() {

    glfwSetWindowUserPointer(window, this);

    // refer to https://www.glfw.org/docs/3.3/group__input.html

    #define LOAD_APP()    \
        GLApp* app = static_cast<GLApp*>(glfwGetWindowUserPointer(window)); \
        if (!app)                                                           \
            return;

    // use OnMouseDown and OnMouseUp
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        LOAD_APP()

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        switch(action) {
            case GLFW_PRESS:    
                app->OnMouseDown(button, xpos, ypos);   break;
            case GLFW_RELEASE:      
                app->OnMouseUp(button, xpos, ypos);     break;
        }
    
    });

    // use OnMouseMove
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        LOAD_APP()

        app->OnMouseMove(xpos, ypos);
    });


    // use OnKeyDown, onKeyHold, and onKeyUp
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        LOAD_APP()

        switch(action) {
            case GLFW_PRESS:
                app->OnKeyDown(key, scancode, mods);    break;
            case GLFW_RELEASE:
                app->OnKeyUp(key, scancode, mods);    break;
            case GLFW_REPEAT:
                app->OnKeyHold(key, scancode, mods);    break;
        }
    });


    return true;
}
