#include <cstring>
#include "baka_logger.h"
#include "baka_vk_utils.h"

namespace baka
{
    /*  =============================================================
        DEBUG MESSENGER
        ============================================================= */
    VkDebugUtilsMessengerCreateInfoEXT VulkanUtils::DebugMessengerCreateInfo(
            VkDebugUtilsMessageSeverityFlagsEXT severity,
            VkDebugUtilsMessageTypeFlagsEXT type,
            PFN_vkDebugUtilsMessengerCallbackEXT callback,
            void *userData)
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = severity;
        createInfo.messageType = type;
        createInfo.pfnUserCallback = callback;
        createInfo.pUserData = userData;
        return createInfo;
    }

    VkDebugUtilsMessengerCreateInfoEXT VulkanUtils::DebugMessengerCreateInfoDefault()
    {
        return VulkanUtils::DebugMessengerCreateInfo(
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            VulkanUtils::DebugCallbackDefault,
            nullptr
        );
    }

    VkResult VulkanUtils::CreateDebugUtilsMessengerEXT(
            VkInstance instance,    
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
            const VkAllocationCallbacks* pAllocator, 
            VkDebugUtilsMessengerEXT* pDebugMessenger) 
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanUtils::DebugCallbackDefault(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData)
    {
        char msgt[128];

        if(messageType <= VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
        {
            if(messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
            {
                strcpy(msgt, "General");
            }

            if(messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
            {
                strcpy(msgt, "Performance");
            }

            if(messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
            {
                strcpy(msgt, "Validation");
            }
        }
        else
        {
            strcpy(msgt, "Unknown");
        }

        if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        {
            bakaerr("%s - %s", msgt, pCallbackData->pMessage);
        }
        else if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        {
            bakawarn("%s - %s", msgt, pCallbackData->pMessage);
        }
        else if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        {
            bakalog("%s - %s", msgt, pCallbackData->pMessage);
        }
        else
        {
            bakawarn("%s(Unknown Severity) - %s", msgt, pCallbackData->pMessage);
        }

        return VK_FALSE;
    }

    /*  ================================================================
        PHYSICAL DEVICE
        ================================================================ */
        std::vector<VkPhysicalDevice> VulkanUtils::GetAvailableDevices(VkInstance instance)
        {
            unsigned int count = 0;
            vkEnumeratePhysicalDevices(instance, &count, nullptr);
            std::vector<VkPhysicalDevice> devices(count);
            vkEnumeratePhysicalDevices(instance, &count, devices.data());
            return devices;
        }

        VkPhysicalDeviceProperties VulkanUtils::GetPhysicalDeviceCapabilities(VkPhysicalDevice device)
        {
            VkPhysicalDeviceProperties prop = {};
            vkGetPhysicalDeviceProperties(device, &prop);
            return prop;
        }

        bool VulkanUtils::IsPhysicalDeviceSuitable(VulkanPhysicalDevice &device, VkSurfaceKHR surface)
        {
            return  device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && 
                    device.queues.FindPresentQueue(surface) &&
                    device.queues.FindQueueIndex( VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT );
        }

    /*  ====================================================================
        LOGICAL DEVICE
        ==================================================================== */
        VkDeviceQueueCreateInfo VulkanUtils::DeviceQueueCreateInfo(
            VkDeviceQueueCreateFlags flags,
            const void *pNext,
            const float *priorities,
            uint32_t queueCount,
            uint32_t queueFamilyIndex)
        {
            VkDeviceQueueCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            info.flags = flags;
            info.pNext = pNext;
            info.pQueuePriorities = priorities;
            info.queueCount = queueCount;
            info.queueFamilyIndex = queueFamilyIndex;
            return info;
        }
}