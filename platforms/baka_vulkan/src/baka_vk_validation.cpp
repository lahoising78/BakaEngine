#include "baka_logger.h"
#include "baka_vk_validation.h"
#include <cstring>

namespace baka
{

    void VulkanValidation::Init()
    {
        unsigned int count = 0;
        vkEnumerateInstanceLayerProperties(&count, nullptr);
        layers.resize(count);
        vkEnumerateInstanceLayerProperties(&count, layers.data());
    }

    bool VulkanValidation::EnableLayer(const char *layer)
    {
        for(auto &l : this->layers)
        {
            if(strcmp( layer, l.layerName ) == 0)
            {
                enabled.push_back(l.layerName);
                bakalog("Enabled validation layer %s", *(enabled.end()-1));
                return true;
            }
        }

        return false;
    }

    uint32_t VulkanValidation::EnableLayers(std::vector<const char *> layers)
    {
        uint32_t count = 0;

        uint32_t i;
        for(i = 0; i < layers.size(); i++)
        {
            if( EnableLayer( layers[i] ) )
            {
                count++;
            }
        }

        return count;
    }
    
} // namespace baka
