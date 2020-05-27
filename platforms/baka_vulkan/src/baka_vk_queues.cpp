#ifdef VULKAN_AVAILABLE
#include "baka_logger.h"
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
        bool found = false;
        for(uint32_t i = 0; i < families.size(); i++)
        {
            if( families[i].queueFlags & flag )
            {
                familyIndices[ flag ] = i;
                found = true;
            }
        }
        if(found) bakalog("using queue %u for queue flag %u", familyIndices[flag], flag);
        return found;
    }

    bool VulkanPhysicalDeviceQueues::FindPresentQueue( VkSurfaceKHR surface )
    {
        VkBool32 presentable = false;
        for(uint32_t i = 0; i < families.size(); i++)
        {
            vkGetPhysicalDeviceSurfaceSupportKHR(this->device, i, surface, &presentable);
            if(presentable)
            {
                familyIndices[ VkQueueFlagBits::VK_QUEUE_FLAG_BITS_MAX_ENUM ] = i;
                presentable = true;
            }
        }

        if( presentable ) bakalog("using queue %u for presentation", familyIndices[VkQueueFlagBits::VK_QUEUE_FLAG_BITS_MAX_ENUM]);
        return presentable;
    }

    bool VulkanPhysicalDeviceQueues::IsIndexReserved( uint32_t index )
    {
        for(auto famid : familyIndices)
        {
            if(famid.second == index) return true;
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
#endif