#ifndef _BAKA_CAMERA_H_
#define _BAKA_CAMERA_H_

#include "baka_camera_base.h"

namespace baka
{
    class OrthographicsCamera : public CameraBase<float>
    {
    public:
        OrthographicsCamera();
    
    private:
        void RecalculateMatrix();
    };

    class Camera : public CameraBase<glm::vec3>
    {
    public:
        Camera(float fov = 45.0f, float farClip = 100.0f, float nearClip = 0.1f);

    private:
        void RecalculateMatrix();

    private:
        float fov;
        float nearClip;
        float farClip;
    };
} // namespace baka

#endif