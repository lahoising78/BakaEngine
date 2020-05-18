#ifndef _BAKA_VULKAN_H_
#define _BAKA_VULKAN_H_

#include "baka_platform.h"
#include <vulkan/vulkan.h>
#include "baka_vk_extensions.h"
#include "baka_vk_validation.h"
#include "baka_vk_physical_device.h"

namespace baka
{
    #ifdef VULKAN_AVAILABLE

    class VulkanGraphics
    {

    public:
        VulkanGraphics(const char *applicationName, bool enableValidations);
        virtual ~VulkanGraphics();
        virtual void Init();

    private:
        virtual void CreateInstance();
        virtual void PickPhysicalDevice();

    protected:
        char applicationName[4096];

        VulkanExtensions extensions;
        
        bool enableValidations;
        VulkanValidation instance_layers;

        /* VULKAN STUFF */
        VkInstance instance;
        VulkanPhysicalDevice physicalDevice;
    };

    #else

    BAKA_PLATFORM_NOT_FOUND(VulkanGraphics)

    #endif
}

#endif