#include <lights/lights_manager.h>

namespace baka
{
    
void LightsManager::ActivateLight(Light *light)
{
    active_lights.insert(light);
}

void LightsManager::DeactivateLight(Light *light)
{
    active_lights.erase(light);
}

void LightsManager::BindLights(Shader *shader)
{
    for(Light *light : active_lights)
    {
        switch (light->GetType())
        {
        case Light::Type::AMBIENT:
            light->Bind(shader, "u_ambientLight");
            break;

        case Light::Type::DIRECTIONAL:
            light->Bind(shader, "u_dirLight");
            break;

        case Light::Type::POINT:
            light->Bind(shader, "u_pointLight");
            break;
        
        default:
            break;
        }
    }
}

} // namespace baka