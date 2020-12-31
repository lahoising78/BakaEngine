#include <baka_graphics.h>
#include <baka_logger.h>

#include <glm/gtc/type_ptr.hpp>

#include <lights/directional_light.h>

namespace baka
{
    DirectionalLight::DirectionalLight() : DirectionalLight(
        glm::vec3(1.0f, 1.0f, 1.0f), 
        1.0f,
        glm::identity<glm::quat>()
    ) {}

    DirectionalLight::DirectionalLight(glm::vec3 color, float intensity, glm::quat rotation)
        : Light(color, intensity, Light::DIRECTIONAL), rotation(rotation) {}

    void DirectionalLight::Bind(Shader *shader, const char *uniformName)
    {
        char buffer[DIR_LIGHT_MAX_NAME] = {0};
        BAKA_ASSERT(shader);
        Light::BindBaseLight(this, shader, uniformName);

        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.dir", uniformName);
        glm::vec3 dir = this->GetDirection();
        shader->SetUniform(
            UniformType::FLOAT3,
            buffer,
            (void*)glm::value_ptr(dir)
        );
    }
} // namespace baka