#include "baka_vk_queues.h"

namespace baka
{
    VulkanQueues::VulkanQueues()
    {
        families.clear();
        familyIndices.clear();
        device = VK_NULL_HANDLE;
    }

    VulkanQueues::VulkanQueues(VkPhysicalDevice device)
    {
        this->device = device;

        unsigned int count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(this->device, &count, nullptr);
        families.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(this->device, &count, families.data());
    }

    bool VulkanQueues::FindQueueIndex( VkQueueFlagBits flag )
    {
        for(uint32_t i = 0; i < families.size(); i++)
        {
            if( families[i].queueFlags & flag )
            {
                familyIndices[ flag ] = i;
                return true;
            }
        }
        return false;
    }
}