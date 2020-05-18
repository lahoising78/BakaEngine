#ifndef _BAKA_VK_PHYSICAL_DEVICE_H_
#define _BAKA_VK_PHYSICAL_DEVICE_H_

#include <vulkan/vulkan.h>
#include "baka_vk_queues.h"

namespace baka
{
    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice()
        {
            this->device = VK_NULL_HANDLE;
            this->properties = {};
            this->features = {};
            this->requiredFeatures.clear();
        }

        VulkanPhysicalDevice(VkPhysicalDevice device, std::vector<VkPhysicalDeviceFeatures> requiredFeatures);

        bool IsSuitable();

        bool FeatureContains(VkPhysicalDeviceFeatures container, VkPhysicalDeviceFeatures check);

    public:
        VulkanPhysicalDeviceQueues queues;
        std::vector<VkPhysicalDeviceFeatures> requiredFeatures;

        VkPhysicalDevice device;
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
    };
}

#endif