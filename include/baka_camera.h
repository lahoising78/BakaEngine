#ifndef _BAKA_CAMERA_H_
#define _BAKA_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace baka
{
    typedef enum
    {
        ORTHOGRAPHIC = 0,
        PERSPECTIVE
    } CameraType;

    typedef union
    {
        struct Ortho
        {
            float width, height;
        } orthoInfo;

        struct Perspective
        {
            float fov;
        } perspectiveInfo;
    } CameraInfo;

    class Camera
    {
    public:
        Camera();
        Camera(CameraType camType, CameraInfo info, float nearClip = 0.1f, float farClip = 100.0f);

        void SetOrtho(CameraInfo::Ortho orthoInfo = {2.0f, 2.0f}, float nearClip = 0.1f, float farClip = 100.0f);
        void SetPerspective(CameraInfo::Perspective perspectiveInfo = {45.0f}, float nearClip = 0.1f, float farClip = 100.0f);

        void Update();

        glm::mat4 GetViewProjection() { return viewProjection; }

        void SetPosition(glm::vec3 pos) { position = pos; RecalculateMatrix(); }

    private:
        void RecalculateMatrix();
        void UpdateCameraSpace();

    private:
        glm::vec3 position;
        glm::quat rotation;

        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 viewProjection;

        CameraType camType;
        CameraInfo info;
        float nearClip;
        float farClip;
    };
} // namespace baka

#endif