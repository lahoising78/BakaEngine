#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "baka_camera.h"
#include "baka_graphics.h"

namespace baka
{
    
extern Graphics *graphics;

OrthographicsCamera::OrthographicsCamera()
    : CameraBase()
{
    this->rotation = 0.0f;

    float width = (float)graphics->GetWindowWidth() / 2;
    float height = (float)graphics->GetWindowHeight() / 2;

    this->projection = glm::ortho(-width, width, -height, height, -1.0f, 1.0f);

    RecalculateMatrix();
}

void OrthographicsCamera::RecalculateMatrix()
{
    this->view = 
        glm::translate( identity_matrix, this->position ) *
        glm::rotate( identity_matrix, glm::radians(this->rotation), glm::vec3(0, 0, 1));
    
    view = glm::inverse(view);

    this->view_projection = this->projection * this->view;
}

Camera::Camera(float fov, float farClip, float nearClip)
    : CameraBase(), fov(fov), nearClip(nearClip), farClip(farClip)
{
    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    RecalculateMatrix();
}

void Camera::RecalculateMatrix()
{
    view = glm::translate(identity_matrix, this->position) * 
        glm::yawPitchRoll(glm::radians(this->rotation.y), glm::radians(this->rotation.x), glm::radians(this->rotation.z));

    float w = graphics->GetWindowWidth();
    float h = graphics->GetWindowHeight();
    projection = glm::perspective(glm::radians(this->fov), w/h, this->nearClip, this->farClip);

    this->view_projection = this->projection * this->view;
}

} // namespace baka
