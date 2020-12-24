#include <baka_logger.h>
#include <lights/ambient_light.h>

namespace baka
{
    
AmbientLight::AmbientLight() 
    : AmbientLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f) {}

AmbientLight::AmbientLight(glm::vec3 color, float intensity) 
    : Light(color, intensity) {}

void AmbientLight::Bind(Shader *shader, const char *uniformName)
{
    BAKA_ASSERT(shader);
    Light::BindBaseLight(this, shader, uniformName);
}

} // namespace baka
