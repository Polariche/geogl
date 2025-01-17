#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include "../../Common/GL/GLApp.h"
#include "../../Common/GL/Transform.h"

using namespace std;

typedef pair<float, float> Point;
typedef pair<unsigned int, unsigned int> Edge;

class TutorialApp_05 : GLApp {
public:
    ~TutorialApp_05() {};

public:
    virtual bool Initialize() override;

public:
    void Run();

protected:
    virtual void OnResize() override {};
    virtual void Update() override;
    virtual void Draw() override;

protected:
    virtual void OnMouseDown(int button, double xpos, double ypos) override;
    virtual void OnMouseUp(int button, double xpos, double ypos) override;
    virtual void OnMouseMove(double xpos, double ypos) override;

    virtual void OnKeyDown(int key, int scancode, int mods) override;
    virtual void OnKeyUp(int key, int scancode, int mods) override;
    virtual void OnKeyHold(int key, int scancode, int mods) override {};

protected:
    Point* ClosestPoint(float xpos, float ypos);

protected:
    vector<Point> points;
    vector<Edge> edges;

    Point* selected_point = NULL;

protected:
    unsigned int vao;

    BufferObject<Point>* vbo;
    BufferObject<Edge>* ibo;
    

protected:
    bool input_up = false;
    bool input_left = false;
    bool input_right = false;
    bool input_down = false;

protected:
    Transform camera;

protected:
    int uniform_mvp;

};


bool TutorialApp_05::Initialize() {
    // init GLApp functionalities
    GLApp::InitOpenGL();
    GLApp::InitShaders("../src/Scenes/tutorials/shaders/vert2.vert", 
                        "../src/Scenes/tutorials/shaders/frag.frag");
    GLApp::InitCallbacks();

    // init render objects
    glGenVertexArrays(1, &vao);

    vbo = new BufferObject<Point>(GL_ARRAY_BUFFER, &points);
    vbo->SetAttribPointer(vao, GL_FLOAT);

    ibo = new BufferObject<Edge>(GL_ELEMENT_ARRAY_BUFFER, &edges);

    // initialize uniform
    uniform_mvp = glGetUniformLocation(shaderProgram, "mvp");

    // init points & edges
    points.push_back({0.0f, 0.5f});
    points.push_back({-0.5f, -0.5f});
    points.push_back({0.5f, -0.5f});

    edges.push_back({0,1});
    edges.push_back({1,2});
    edges.push_back({2,0});

    return true;
}

void TutorialApp_05::Run() {
    GLApp::Run();
}

void TutorialApp_05::Update() {
    glm::vec3 diff = glm::vec3(0.0f);
    glm::vec3 pos;
    const float diff_x = 0.001f;

    if (input_up)
        diff += glm::vec3(0.0f, diff_x, 0.0f);
    if (input_left)
        diff += glm::vec3(-diff_x, 0.0f, 0.0f);
    if (input_right)
        diff += glm::vec3(diff_x, 0.0f, 0.0f);
    if (input_down)
        diff += glm::vec3(0.0f, -diff_x, 0.0f);

    pos = camera.GetPosition() + diff;
    camera.SetPosition(pos);

}

void TutorialApp_05::Draw() {
    vbo->BufferData();
    ibo->BufferData();

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    glUniformMatrix4fv(uniform_mvp, 1, false, &camera.GetMatrix()[0][0]);

    vbo->Bind();
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, points.size());
    vbo->Unbind();

    ibo->Bind();
    glLineWidth(2.0f);
    glDrawElements(GL_LINES, 2 * edges.size(), GL_UNSIGNED_INT, nullptr);
    ibo->Unbind();
    
    glBindVertexArray(0);
}

void TutorialApp_05::OnMouseDown(int button, double xpos, double ypos) {
    // select the closest point
    glm::vec3 campos = camera.GetPosition();
    xpos = (xpos / width) * 2 - 1 - campos.x;
    ypos = -(ypos / height) * 2 + 1 - campos.y;

    cout << xpos << " " << ypos << "\n";
    
    Point* closest = ClosestPoint(xpos, ypos);

    if (!!closest) {
        cout << closest->first << " " << closest->second << "\n";
        selected_point = closest;
    }
}

void TutorialApp_05::OnMouseUp(int button, double xpos, double ypos) {
    selected_point = NULL;
}

void TutorialApp_05::OnMouseMove(double xpos, double ypos) {
    glm::vec3 campos = camera.GetPosition();
    xpos = (xpos / width) * 2 - 1 - campos.x;
    ypos = -(ypos / height) * 2 + 1 - campos.y;

    if (!!selected_point) {
        selected_point->first = xpos;
        selected_point->second = ypos;
    }
}

void TutorialApp_05::OnKeyDown(int key, int scancode, int mods) {
    switch(key) {
        case GLFW_KEY_W:  input_up = true;      break;
        case GLFW_KEY_A:  input_left = true;    break;
        case GLFW_KEY_S:  input_down = true;    break;
        case GLFW_KEY_D:  input_right = true;   break;
    }
}

void TutorialApp_05::OnKeyUp(int key, int scancode, int mods) {
    switch(key) {
        case GLFW_KEY_W:  input_up = false;      break;
        case GLFW_KEY_A:  input_left = false;    break;
        case GLFW_KEY_S:  input_down = false;    break;
        case GLFW_KEY_D:  input_right = false;   break;
    }
}


Point* TutorialApp_05::ClosestPoint(float x, float y) {
    Point cursor = {x, y};
    
    Point* candidate = NULL;
    double min_dist = 0.05;

    for (Point & p : points) {
        double dist = sqrt((p.first - x)*(p.first - x) + (p.second - y)*(p.second - y));
        if (dist < min_dist) {
            min_dist = dist;
            candidate = &p;
        }
    }

    return candidate;
}



int main () {
    TutorialApp_05 app;

    app.Initialize();
    app.Run();

    return 0;
}
