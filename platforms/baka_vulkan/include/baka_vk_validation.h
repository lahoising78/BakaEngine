#ifndef _BAKA_VK_VALIDATION_H_
#define _BAKA_VK_VALIDATION_H_

#include <vulkan/vulkan.h>
#include <vector>

namespace baka
{

    class VulkanValidation
    {
    public:
        void Init();
        bool EnableLayer(const char *layer);
        uint32_t EnableLayers(std::vector<const char *> layers);

    public:
        std::vector<VkLayerProperties> layers;
        std::vector<const char *> enabled;
    };
    
} // namespace baka


#endif