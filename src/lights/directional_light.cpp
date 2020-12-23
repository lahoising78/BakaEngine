#include <baka_graphics.h>
#include <baka_logger.h>

#include <glm/gtc/type_ptr.hpp>

#include <lights/directional_light.h>

#define DIR_LIGHT_MAX_NAME 64

namespace baka
{
    DirectionalLight::DirectionalLight() : DirectionalLight(
        glm::vec3(1.0f, 1.0f, 1.0f), 
        1.0f,
        glm::identity<glm::quat>()
    ) {}

    DirectionalLight::DirectionalLight(glm::vec3 color, float intensity, glm::quat rotation)
        : Light(color, intensity), rotation(rotation) {}

    void DirectionalLight::Bind(Shader *shader, const char *uniformName)
    {
        char buffer[DIR_LIGHT_MAX_NAME] = {0};
        BAKA_ASSERT(shader);
        
        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.color", uniformName);
        shader->SetUniform(
            Shader::Type::FLOAT3, 
            buffer, 
            (void*)glm::value_ptr(this->color)
        );

        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.intensity", uniformName);
        shader->SetUniform(
            Shader::Type::FLOAT,
            buffer,
            &this->intensity
        );

        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.dir", uniformName);
        glm::vec3 dir = this->GetDirection();
        shader->SetUniform(
            Shader::Type::FLOAT3,
            buffer,
            (void*)glm::value_ptr(dir)
        );
    }
} // namespace baka