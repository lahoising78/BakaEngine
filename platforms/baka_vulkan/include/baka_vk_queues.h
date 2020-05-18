#ifndef _BAKA_VK_QUEUES_H_
#define _BAKA_VK_QUEUES_H_

#include <vector>
#include <unordered_map>
#include <vulkan/vulkan.h>

namespace baka
{
    class VulkanQueues
    {
    public:
        VulkanQueues();
        VulkanQueues(VkPhysicalDevice device);
        bool FindQueueIndex( VkQueueFlagBits flag );

    public:
        std::vector<VkQueueFamilyProperties> families;
        std::unordered_map<VkQueueFlagBits, uint32_t> familyIndices;
        VkPhysicalDevice device;
    };
}

#endif