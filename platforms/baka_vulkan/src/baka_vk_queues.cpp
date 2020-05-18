#include "baka_vk_queues.h"

namespace baka
{
    /*  ======================================================
        PHYSICAL DEVICE QUEUES
        ====================================================== */
    VulkanPhysicalDeviceQueues::VulkanPhysicalDeviceQueues()
    {
        families.clear();
        familyIndices.clear();
    }

    VulkanPhysicalDeviceQueues::VulkanPhysicalDeviceQueues(VkPhysicalDevice device)
    {
        this->device = device;

        unsigned int count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(this->device, &count, nullptr);
        families.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(this->device, &count, families.data());
    }

    bool VulkanPhysicalDeviceQueues::FindQueueIndex( VkQueueFlagBits flag )
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

    /*  ==============================================================
        LOGICAL DEVICE QUEUES
        ============================================================== */
    VulkanLogicalDeviceQueues::VulkanLogicalDeviceQueues()
    {
        this->device = VK_NULL_HANDLE;
        this->familyIndex = 0;
        this->queueIndex = 0;
        this->queue = VK_NULL_HANDLE;
    }

    VulkanLogicalDeviceQueues::VulkanLogicalDeviceQueues(VkDevice device, uint32_t familyIndex, uint32_t queueIndex)
    {
        this->device = device;
        this->familyIndex = familyIndex;
        this->queueIndex = queueIndex;

        vkGetDeviceQueue(this->device, familyIndex, queueIndex, &queue);
    }
}