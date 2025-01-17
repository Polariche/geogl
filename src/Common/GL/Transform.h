#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>

class Transform {
private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    
    glm::mat4 matrix;

public:
    Transform();
    
    glm::vec3 GetPosition();
    glm::quat GetRotation();
    glm::vec3 GetScale();

    glm::mat4 GetMatrix();

    void SetPosition(glm::vec3 position);
    void SetRotation(glm::quat quaternion);
    void SetRotation(glm::vec3 eulerAngles);
    void SetScale(glm::vec3 scale);

private:
    void UpdateMatrix();

};