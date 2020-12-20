#ifndef _BAKA_DIRECTIONAL_LIGHT_H_
#define _BAKA_DIRECTIONAL_LIGHT_H_

#include <lights/baka_lights.h>
#include <glm/gtc/quaternion.hpp>

namespace baka
{
    
class DirectionalLight : public Light
{
public:
    DirectionalLight();
    DirectionalLight(glm::vec4 color, float intensity, glm::quat rot);
    glm::vec3 GetDirection() { return rotation * glm::vec3(0.0f, 0.0f, 1.0f); }

public:
    glm::quat rotation; // direction is forward according to rotation
};

} // namespace baka

#endif