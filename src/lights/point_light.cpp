#include <glm/gtc/type_ptr.hpp>

#include <baka_logger.h>
#include <lights/point_light.h>

namespace baka
{

PointLight::PointLight() 
    : PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f)) {}

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 position)
    : Light(color, intensity)
{
    this->position = position;
}

void PointLight::Bind(Shader *shader, const char *uniformName)
{
    char buffer[DIR_LIGHT_MAX_NAME];
    BAKA_ASSERT(shader);
    Light::BindBaseLight(this, shader, uniformName);

    snprintf(buffer, DIR_LIGHT_MAX_NAME, "%s.position", uniformName);
    shader->SetUniform(
        baka::Shader::Type::FLOAT3,
        buffer,
        (void*)glm::value_ptr(this->position)
    );
}

}