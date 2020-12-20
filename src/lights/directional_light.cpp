#include <baka_graphics.h>

#include <lights/directional_light.h>

namespace baka
{
    DirectionalLight::DirectionalLight() : DirectionalLight(
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
        1.0f,
        glm::identity<glm::quat>()
    ) {}

    DirectionalLight::DirectionalLight(glm::vec4 color, float intensity, glm::quat rotation)
        : Light(color, intensity), rotation(rotation) {}
} // namespace baka