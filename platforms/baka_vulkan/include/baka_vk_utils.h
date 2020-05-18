#ifndef _BAKA_VK_UTILS_H_
#define _BAKA_VK_UTILS_H_

#include <vulkan/vulkan.h>

namespace baka
{
    class VulkanUtils
    {
    public:
        static VkDebugUtilsMessengerCreateInfoEXT DebugMessengerCreateInfo(
            VkDebugUtilsMessageSeverityFlagsEXT severity,
            VkDebugUtilsMessageTypeFlagsEXT type,
            PFN_vkDebugUtilsMessengerCallbackEXT callback,
            void *userData
        );

        static VkDebugUtilsMessengerCreateInfoEXT DebugMessengerCreateInfoDefault();

        static VkResult CreateDebugUtilsMessengerEXT(
            VkInstance instance,    
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
            const VkAllocationCallbacks* pAllocator, 
            VkDebugUtilsMessengerEXT* pDebugMessenger);

    private:
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallbackDefault(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
    };
}

#endif