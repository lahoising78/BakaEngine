#ifndef _BAKA_LIGHTS_LIGHTS_MANAGER_H_
#define _BAKA_LIGHTS_LIGHTS_MANAGER_H_

#include <baka_lights.h>
#include <unordered_set>

namespace baka
{
    
class LightsManager
{
public:
    static LightsManager &Get()
    {
        static LightsManager manager = LightsManager();
        return manager;
    }

    void ActivateLight(Light *light);
    void DeactivateLight(Light *light);
    void BindLights(Shader *shader);

private:
    LightsManager(){ active_lights.clear(); }
    std::unordered_set<Light*> active_lights;
};

} // namespace baka


#endif