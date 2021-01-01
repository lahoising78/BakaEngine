#include <glm/gtc/type_ptr.hpp>
#include <lights/light.h>

namespace baka
{
    void Light::BindBaseLight(Light *light, Shader *shader, const char *uniformName)
    {
        char buffer[DIR_LIGHT_MAX_NAME] = {0};
        
        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.light.color", uniformName);
        shader->SetUniform(
            UniformType::UNIFORM_FLOAT3, 
            buffer, 
            (void*)glm::value_ptr(light->color)
        );

        snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.light.intensity", uniformName);
        shader->SetUniform(
            UniformType::UNIFORM_FLOAT,
            buffer,
            &light->intensity
        );
    }
} // namespace baka