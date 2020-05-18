#ifndef _BAKA_VK_PHYSICAL_DEVICE_H_
#define _BAKA_VK_PHYSICAL_DEVICE_H_

#include <vulkan/vulkan.h>

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
        }

        VulkanPhysicalDevice(VkPhysicalDevice device);

    public:
        VkPhysicalDevice device;
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
    };
}

#endif