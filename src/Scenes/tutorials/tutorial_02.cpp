#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include "../../Common/GL/GLApp.h"
// #include "../Common/Models/Point.h"

using namespace std;

typedef pair<float, float> Point;

class TutorialApp_02 : GLApp {
public:
    ~TutorialApp_02() {};

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
    Point* selected_point = NULL;

};


bool TutorialApp_02::Initialize() {
    // init GLApp functionalities
    GLApp::InitOpenGL();
    GLApp::InitCallbacks();

    points.push_back({0.0f, 0.5f});
    points.push_back({-0.5f, -0.5f});
    points.push_back({0.5f, -0.5f});

    return true;
}

void TutorialApp_02::Run() {
    GLApp::Run();
}

void TutorialApp_02::Draw() {
    glBegin(GL_TRIANGLES);
    for (auto &[x, y] : points)
        glVertex2f(x, y);
    glEnd();
}

void TutorialApp_02::OnMouseDown(int button, double xpos, double ypos) {
    // select the closest point
    xpos = (xpos / width) * 2 - 1;
    ypos = -(ypos / height) * 2 + 1;
    
    Point* closest = ClosestPoint(xpos, ypos);

    if (!!closest) {
        cout << closest->first << " " << closest->second << "\n";
        selected_point = closest;
    }
}

void TutorialApp_02::OnMouseUp(int button, double xpos, double ypos) {
    selected_point = NULL;
}

void TutorialApp_02::OnMouseMove(double xpos, double ypos) {
    xpos = (xpos / width) * 2 - 1;
    ypos = -(ypos / height) * 2 + 1;

    if (!!selected_point) {
        selected_point->first = xpos;
        selected_point->second = ypos;
    }
}

Point* TutorialApp_02::ClosestPoint(float x, float y) {
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
    TutorialApp_02 app;

    app.Initialize();
    app.Run();

    return 0;
}
