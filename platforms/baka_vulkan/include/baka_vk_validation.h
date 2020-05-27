#ifndef _BAKA_VK_VALIDATION_H_
#define _BAKA_VK_VALIDATION_H_

#ifdef VULKAN_AVAILABLE
#include <vulkan/vulkan.h>
#include <vector>

namespace baka
{

    class VulkanValidation
    {
    friend class VulkanGraphics;
    public:
        void Init();
        bool EnableLayer(const char *layer);
        uint32_t EnableLayers(std::vector<const char *> layers);
        uint32_t EnableAllAvailable();
        void DisableLayer(const char *layer);

        /* STATIC METHODS */
        static void SetupDebugMessenger(VkInstance instance);
        
    private:
        /* STATIC METHODS */
        static void DestroyDebugUtilsMessengerEXT(
            VkInstance instance, 
            VkDebugUtilsMessengerEXT debugMessenger, 
            const VkAllocationCallbacks* pAllocator);
        
        static void DestroyDebugMessenger(VkInstance instance);
        

    public:
        std::vector<VkLayerProperties> layers;
        std::vector<const char *> enabled;
    };
    
} // namespace baka

#endif
#endif