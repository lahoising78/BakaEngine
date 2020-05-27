#ifndef _BAKA_VK_PHYSICAL_DEVICE_H_
#define _BAKA_VK_PHYSICAL_DEVICE_H_

#ifdef VULKAN_AVAILABLE
#include <vulkan/vulkan.h>
#include "baka_vk_queues.h"
#include "baka_vk_extensions.h"

namespace baka
{
    class VulkanSwapchain;

    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice()
        {
            this->device = VK_NULL_HANDLE;
            this->properties = {};
            this->features = {};
            this->extensions.Init();
            this->enabledFeatures = {};
        }

        VulkanPhysicalDevice(VkPhysicalDevice device);

        bool IsSuitable( VulkanSwapchain *swapchain, VkSurfaceKHR surface, std::vector<const char *> requiredExtensions  );

        bool FeatureContains(VkPhysicalDeviceFeatures container, VkPhysicalDeviceFeatures check);

    public:
        VulkanPhysicalDeviceQueues queues;
        
        VulkanDeviceExtensions extensions;

        VkPhysicalDevice device;
        VkPhysicalDeviceProperties properties;

        VkPhysicalDeviceFeatures features;
        VkPhysicalDeviceFeatures enabledFeatures;
    };
}
#endif

#endif