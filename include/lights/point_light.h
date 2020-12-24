#ifndef _BAKA_LIGHTS_POINT_LIGHT_H_
#define _BAKA_LIGHTS_POINT_LIGHT_H_

#include <lights/baka_lights.h>

namespace baka
{
    
class PointLight : public Light
{
public:
    PointLight();
    PointLight(glm::vec3 color, float intensity = 1.0f, glm::vec3 position = {0.0f, 0.0f, 0.0f});

    void Bind(Shader *shader, const char *uniformName) override;

public:
    glm::vec3 position;
};

} // namespace baka

#endif