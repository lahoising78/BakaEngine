#ifndef _BAKA_VK_DEVICE_H_
#define _BAKA_VK_DEVICE_H_

#include <unordered_map>
#include <vulkan/vulkan.h>
#include "baka_vk_queues.h"
#include "baka_vk_physical_device.h"

namespace baka
{
    // class VulkanLogicalDevice
    // {
    // public:
    //     VulkanPhysicalDevice *physicalDevice;
    //     VkDevice device;
    //     std::unordered_map<VkQueueFlagBits, VulkanLogicalDeviceQueues> queues;
    // };

    typedef struct 
    {
        VulkanPhysicalDevice *physicalDevice;
        VkDevice device;
        std::unordered_map<VkQueueFlagBits, VulkanLogicalDeviceQueues> queues;
    } VulkanLogicalDevice;
}

#endif