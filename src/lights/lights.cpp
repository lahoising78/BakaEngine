#include <glm/gtc/type_ptr.hpp>
#include <lights/baka_lights.h>

namespace baka
{
    void Light::BindBaseLight(Light *light, Shader *shader, const char *uniformName)
    {
        char buffer[DIR_LIGHT_MAX_NAME] = {0};
        
        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.light.color", uniformName);
        shader->SetUniform(
            Shader::Type::FLOAT3, 
            buffer, 
            (void*)glm::value_ptr(light->color)
        );

        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.light.intensity", uniformName);
        shader->SetUniform(
            Shader::Type::FLOAT,
            buffer,
            &light->intensity
        );
    }
} // namespace baka