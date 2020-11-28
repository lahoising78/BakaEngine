#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <baka_input.h>
#include "baka_camera.h"
#include "baka_graphics.h"

namespace baka
{
    
Camera::Camera()
    : position(glm::vec3()), rotation(glm::identity<glm::quat>()), 
    view(glm::mat4(1.0f)), projection(glm::mat4(1.0f)), viewProjection(glm::mat4(1.0f)),
    nearClip(0.1f), farClip(100.0f)
{

}

Camera::Camera(CameraType camType, CameraInfo info, float nearClip, float farClip)
    : position(glm::vec3()), rotation(glm::identity<glm::quat>())
{
    this->camType = camType;
    this->info = info;
    this->nearClip = nearClip;
    this->farClip = farClip;
    UpdateCameraSpace();
}

void Camera::SetPerspective(CameraInfo::Perspective perspectiveInfo, float nearClip, float farClip)
{
    static Graphics &graphics = Graphics::Get();
    
    camType = CameraType::PERSPECTIVE;
    this->info.perspectiveInfo = perspectiveInfo;
    this->nearClip = nearClip;
    this->farClip = farClip;
    
    int w, h;
    graphics.GetWindowSize(&w, &h);
    projection = glm::perspective(perspectiveInfo.fov, (float)w / (float)h , nearClip, farClip);
    RecalculateMatrix();
}

void Camera::SetOrtho(CameraInfo::Ortho orthoInfo, float nearClip, float farClip)
{
    float halfWidth =  orthoInfo.width / 2.0f;
    float halfHeight = orthoInfo.height / 2.0f;
    
    camType = CameraType::ORTHOGRAPHIC;
    this->info.orthoInfo = orthoInfo;
    this->nearClip = nearClip;
    this->farClip = farClip;

    projection = glm::ortho( -halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip );
    RecalculateMatrix();
}

void Camera::RecalculateMatrix()
{
    // view =  glm::yawPitchRoll(glm::yaw(rotation), glm::pitch(rotation), glm::roll(rotation)) *
    //         glm::translate(glm::mat4(1.0f), position);

    // glm::inverse(view);
    glm::vec3 up = rotation * glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 fwd = rotation * glm::vec3(0.0f, 0.0f, 1.0f);
    view = glm::lookAt(
        position,
        position + fwd,
        up
    );
    viewProjection = projection * view;
}

void Camera::Update()
{
    static Input &input = Input::Get();
    if(input.WindowResizedThisFrame())
    {
        UpdateCameraSpace();
    }
}

void Camera::UpdateCameraSpace()
{
    switch (camType)
    {
    case CameraType::ORTHOGRAPHIC:
        SetOrtho(info.orthoInfo, nearClip, farClip);
        break;
    
    case CameraType::PERSPECTIVE:
        SetPerspective(info.perspectiveInfo, nearClip, farClip);
        break;
    
    default:
        break;
    }
}

} // namespace baka
