#ifndef _BAKA_VULKAN_H_
#define _BAKA_VULKAN_H_

#include "baka_platform.h"

#ifdef VULKAN_AVAILABLE
#include <vulkan/vulkan.h>
#include "baka_vk_extensions.h"
#include "baka_vk_validation.h"
#include "baka_vk_physical_device.h"
#include "baka_vk_device.h"
#include "baka_vk_swapchain.h"
#endif


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
        virtual void CreateSurface();
        virtual void PickPhysicalDevice();
        virtual void CreateLogicalDevice();

    protected:
        char applicationName[4096];

        VulkanInstanceExtensions instance_extensions;
        
        bool enableValidations;
        VulkanValidation instance_layers;

        VulkanSwapchain swapchain;

        /* VULKAN STUFF */
        VkInstance instance;
        VulkanPhysicalDevice physicalDevice;
        VulkanLogicalDevice logicalDevice;
        VkSurfaceKHR surface;
    };

    #else

    BAKA_PLATFORM_NOT_FOUND(VulkanGraphics)

    #endif
}

#endif