
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
    
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

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

bool GLApp::InitShaders() {
//     shaderProgram = glCreateProgram();

//     std::string vertexShaderSource = load_text("../src/shaders/vert.vert");
//     if (!vertexShaderSource.empty()) {
//         vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
//         vertexShader->Attach(shaderProgram);
//         vertexShader->Delete();
//     }

//     std::string geometryShaderSource = load_text("../src/shaders/geom.geom");
//     if (!geometryShaderSource.empty()) {
//         geometryShader = new Shader(GL_GEOMETRY_SHADER, geometryShaderSource.c_str());
//         geometryShader->Attach(shaderProgram);
//         geometryShader->Delete();
//     }

//     std::string fragmentShaderSource = load_text("../src/shaders/frag.frag");
//     if (!fragmentShaderSource.empty()) {
//         fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
//         fragmentShader->Attach(shaderProgram);
//         fragmentShader->Delete();
//     }

//     glLinkProgram(shaderProgram);
    

    return true;
}

bool GLApp::InitCallbacks() {

    glfwSetWindowUserPointer(window, this);

    // use OnMouseDown and OnMouseUp
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        GLApp* app = static_cast<GLApp*>(glfwGetWindowUserPointer(window));
        if (!app)
            return;

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if(GLFW_PRESS == action)
            app->OnMouseDown(button, xpos, ypos);
        else if(GLFW_RELEASE == action)
            app->OnMouseUp(button, xpos, ypos);
    });

    // use OnMouseMove
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        GLApp* app = static_cast<GLApp*>(glfwGetWindowUserPointer(window));
        if (!app)
            return;

        app->OnMouseMove(xpos, ypos);
    });


    return true;
}
