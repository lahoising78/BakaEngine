#include "baka_vk_physical_device.h"

namespace baka
{
    VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device)
    {
        if(device == VK_NULL_HANDLE) return;

        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);
        this->device = device;
    }
}