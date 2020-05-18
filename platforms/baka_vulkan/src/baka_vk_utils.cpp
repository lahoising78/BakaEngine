#include <cstring>
#include "baka_logger.h"
#include "baka_vk_utils.h"

namespace baka
{
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
}