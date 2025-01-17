#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Transform.h"


Transform::Transform()
{
    position = glm::vec3(0.0F);
    rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f);
}

glm::vec3 Transform::GetPosition()
{
    return position;
}
glm::quat Transform::GetRotation()
{
    return rotation;
}
glm::vec3 Transform::GetScale()
{
    return scale;
}

glm::mat4 Transform::GetMatrix()
{
    return matrix;
}

void Transform::SetPosition(glm::vec3 position)
{
    this->position = position;
    UpdateMatrix();
}
void Transform::SetRotation(glm::quat quaternion)
{
    this->rotation = quaternion;
    UpdateMatrix();
}
void Transform::SetRotation(glm::vec3 eulerAngles)
{
    this->rotation = glm::quat(eulerAngles);
    UpdateMatrix();
}
void Transform::SetScale(glm::vec3 scale)
{
    this->scale = scale;
    UpdateMatrix();
}

void Transform::UpdateMatrix()
{
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMat = glm::toMat4(rotation);
    glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);

    matrix = translation * rotationMat * scaling;
}