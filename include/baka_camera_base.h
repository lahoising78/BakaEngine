#ifndef _BAKA_CAMERA_BASE_H_
#define _BAKA_CAMERA_BASE_H_

#include <glm/glm.hpp>

namespace baka
{

static glm::mat4 identity_matrix = glm::mat4(1.0f);
    
template<typename Rot>
class CameraBase
{
public:

    CameraBase()
        : position(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        view = identity_matrix;
        projection = identity_matrix;
        view_projection = identity_matrix;
    }
    
    void SetPosition(glm::vec3 position) { this->position = position; RecalculateMatrix(); }
    glm::vec3 GetPosition() { return this->position; }

    glm::mat4 GetViewProjection() { return view_projection; }

    void SetRotation(Rot rotation) { this->rotation = rotation; RecalculateMatrix(); }
    Rot GetRotation() { return this->rotation; }

private:
    virtual void RecalculateMatrix() = 0;

protected:
    glm::vec3 position;
    Rot rotation;

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 view_projection;
};

} // namespace baka

#endif