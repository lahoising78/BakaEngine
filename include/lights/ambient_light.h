#ifndef _BAKA_LIGHTS_AMBIENT_LIGHT_H_
#define _BAKA_LIGHTS_AMBIENT_LIGHT_H_

#include <glm/gtc/quaternion.hpp>
#include <lights/light.h>

namespace baka
{
    
class AmbientLight : public Light
{
public:
    AmbientLight();
    AmbientLight(glm::vec3 color, float intensity = 1.0f);

    void Bind(Shader *shader, const char *uniformName) override;
    
};

} // namespace baka

#endif