#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include "../../Common/GL/GLApp.h"
// #include "../Common/Models/Point.h"

using namespace std;

typedef pair<float, float> Point;
typedef pair<unsigned int, unsigned int> Edge;

class TutorialApp_03 : GLApp {
public:
    ~TutorialApp_03() {};

public:
    virtual bool Initialize() override;

public:
    void Run();

protected:
    virtual void OnResize() override {};
    virtual void Update() override {};
    virtual void Draw() override;

protected:
    virtual void OnMouseDown(int button, double xpos, double ypos) override;
    virtual void OnMouseUp(int button, double xpos, double ypos) override;
    virtual void OnMouseMove(double xpos, double ypos) override;

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

};


bool TutorialApp_03::Initialize() {
    // init GLApp functionalities
    GLApp::InitOpenGL();
    GLApp::InitCallbacks();

    // init render objects
    glGenVertexArrays(1, &vao);

    vbo = new BufferObject<Point>(GL_ARRAY_BUFFER, &points);
    vbo->SetAttribPointer(vao, GL_FLOAT);

    ibo = new BufferObject<Edge>(GL_ELEMENT_ARRAY_BUFFER, &edges);

    // init points & edges
    points.push_back({0.0f, 0.5f});
    points.push_back({-0.5f, -0.5f});
    points.push_back({0.5f, -0.5f});

    edges.push_back({0,1});
    edges.push_back({1,2});
    edges.push_back({2,0});

    return true;
}

void TutorialApp_03::Run() {
    GLApp::Run();
}

void TutorialApp_03::Draw() {
    vbo->BufferData();
    ibo->BufferData();

    glBindVertexArray(vao);

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

void TutorialApp_03::OnMouseDown(int button, double xpos, double ypos) {
    // select the closest point
    xpos = (xpos / width) * 2 - 1;
    ypos = -(ypos / height) * 2 + 1;
    
    Point* closest = ClosestPoint(xpos, ypos);

    if (!!closest) {
        cout << closest->first << " " << closest->second << "\n";
        selected_point = closest;
    }
}

void TutorialApp_03::OnMouseUp(int button, double xpos, double ypos) {
    selected_point = NULL;
}

void TutorialApp_03::OnMouseMove(double xpos, double ypos) {
    xpos = (xpos / width) * 2 - 1;
    ypos = -(ypos / height) * 2 + 1;

    if (!!selected_point) {
        selected_point->first = xpos;
        selected_point->second = ypos;
    }
}

Point* TutorialApp_03::ClosestPoint(float x, float y) {
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
    TutorialApp_03 app;

    app.Initialize();
    app.Run();

    return 0;
}
