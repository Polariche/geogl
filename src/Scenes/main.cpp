#include <iostream>
#include <cstdio>
#include <vector>

#include "../Common/GL/GLApp.h"
#include "../Common/Models/Point.h"

using namespace std;

typedef pair<unsigned int,unsigned int> Edge;

class MainApp : GLApp {
public:
    ~MainApp();

public:
    virtual bool Initialize() override;

public:
    void Run();

protected:
    virtual void OnResize() override;
    virtual void Update() override;
    virtual void Draw() override;

protected:
    virtual void OnMouseDown(int button, double xpos, double ypos) override;
    virtual void OnMouseUp(int button, double xpos, double ypos) override;
    virtual void OnMouseMove(double xpos, double ypos) override;

protected:
    virtual bool InitRenderObjects();
    virtual bool InitWorld();

protected:
    Point* ClosestPoint(float xpos, float ypos, vector<Point*> & excludes);

    void AddPoint(Point p);
    void DeletePoint(int idx);

    void AddEdge(Edge e);
    void DeleteEdge(int idx);

protected:
    vector<Point> points;
    vector<Edge> edges;

    Point* selected_point = NULL;

protected:
    unsigned int vao;

    BufferObject<Point>* vbo;
    BufferObject<Edge>* ibo;

};



MainApp::~MainApp() {
}


bool MainApp::Initialize() {
    // init GLApp functionalities
    GLApp::InitOpenGL();
    GLApp::InitCallbacks();

    InitRenderObjects();
    InitWorld();

    return true;
}

void MainApp::Run() {
    GLApp::Run();
}

void MainApp::OnResize() {
}

void MainApp::Update() {
}

bool MainApp::InitRenderObjects() {
    glGenVertexArrays(1, &vao);

    vbo = new BufferObject<Point>(GL_ARRAY_BUFFER, &points);
    vbo->SetAttribPointer(vao, GL_FLOAT);

    ibo = new BufferObject<Edge>(GL_ELEMENT_ARRAY_BUFFER, &edges);

    return true;
}

bool MainApp::InitWorld() {
    AddPoint({0.0f, 0.5f});
    AddPoint({-0.5f, -0.5f});
    AddPoint({0.5f, -0.5f});
    AddPoint({0.5f, 0.5f});

    AddEdge({0, 1});
    AddEdge({2, 3});

    return true;
}

void MainApp::Draw() {
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

void MainApp::OnMouseDown(int button, double xpos, double ypos) {
    // select the closest point
    xpos = (xpos / width) * 2 - 1;
    ypos = -(ypos / height) * 2 + 1;
    
    vector<Point*> excludes;
    Point* closest = ClosestPoint(xpos, ypos, excludes);

    
    if (!!closest) {
        int idx = (int) (closest - points.data());

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            selected_point = closest;

        } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            DeletePoint(idx);

        } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            AddPoint({(float) xpos, (float) ypos});
            selected_point = &points.back();

            AddEdge({idx, points.size()-1});
        }

    } else {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            AddPoint({(float) xpos, (float) ypos});
    }
}

void MainApp::OnMouseUp(int button, double xpos, double ypos) {
    xpos = (xpos / width) * 2 - 1;
    ypos = -(ypos / height) * 2 + 1;

    // Left-clicked
    if (button == GLFW_MOUSE_BUTTON_LEFT) {   
        // unselect
        selected_point = NULL;
    }

    // Right-clicked
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {   
        if (!selected_point)
            return;

        vector<Point*> excludes = {selected_point};
        Point* closest = ClosestPoint(xpos, ypos, excludes);

        if (!!closest) {
            edges.back().second = (unsigned int) (closest - points.data());
            DeletePoint(points.size()-1);
        } else {
            // DeletePoint(points.size()-1);
        }

        // unselect
        selected_point = NULL;
    }
}

void MainApp::OnMouseMove(double xpos, double ypos) {
    // if there's a selected point, move it to the cursor

    xpos = (xpos / width) * 2 - 1;
    ypos = -(ypos / height) * 2 + 1;

    if (!!selected_point) {
        selected_point->x = xpos;
        selected_point->y = ypos;
    }
}

Point* MainApp::ClosestPoint(float x, float y, vector<Point*> & excludes) {
    Point cursor = {x, y};
    
    Point* candidate = NULL;
    double min_dist = 0.05;

    for (Point & p : points) {
        bool skip = false;

        for (Point * q : excludes) {
            if (&p == q)
                skip = true;
        }
        
        if (skip)
            continue;

        double dist = p.Distance(cursor);
        if (dist < min_dist) {
            min_dist = dist;
            candidate = &p;
        }
    }

    return candidate;
}

void MainApp::AddPoint(Point p) {
    points.push_back(p);
}

void MainApp::DeletePoint(int idx) {
    points.erase(points.begin() + idx);

    for (int i=edges.size()-1;i>=0;i--) {
        if (edges[i].first == idx || edges[i].second == idx)
            DeleteEdge(i);
        else {
            if (edges[i].first > idx)
                edges[i].first--;
            if (edges[i].second > idx)
                edges[i].second--;
        }
    }
}

void MainApp::AddEdge(Edge e) {
    edges.push_back(e);
}

void MainApp::DeleteEdge(int idx) {
    edges.erase(edges.begin() + idx);
}

int main () {
    MainApp app;

    app.Initialize();
    app.Run();

    return 0;
}
