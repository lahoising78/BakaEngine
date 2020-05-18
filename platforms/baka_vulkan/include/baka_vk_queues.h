#ifndef _BAKA_VK_QUEUES_H_
#define _BAKA_VK_QUEUES_H_

#include <vector>
#include <unordered_map>
#include <vulkan/vulkan.h>

namespace baka
{
    class VulkanPhysicalDeviceQueues
    {
    public:
        VulkanPhysicalDeviceQueues();
        VulkanPhysicalDeviceQueues(VkPhysicalDevice device);
        bool FindQueueIndex( VkQueueFlagBits flag );

    public:
        std::vector<VkQueueFamilyProperties> families;
        std::unordered_map<VkQueueFlagBits, uint32_t> familyIndices;
        VkPhysicalDevice device;
    };

    class VulkanLogicalDeviceQueues
    {
    public:
        VulkanLogicalDeviceQueues();
        VulkanLogicalDeviceQueues(VkDevice device, uint32_t familyIndex, uint32_t queueIndex);

    public:
        uint32_t familyIndex;
        uint32_t queueIndex;
        VkDevice device;
        VkQueue queue;
    };
}

#endif