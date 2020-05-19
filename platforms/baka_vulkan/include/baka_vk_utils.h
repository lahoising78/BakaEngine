#ifndef _BAKA_VK_UTILS_H_
#define _BAKA_VK_UTILS_H_

#include <vector>
#include <vulkan/vulkan.h>
#include "baka_vk_physical_device.h"

#define VKASSERT(res, func, msg) \
res = func; \
if( res != VK_SUCCESS ) \
{ bakawarn("%s failed with error code: %d", msg, res); }

namespace baka
{
    class VulkanUtils
    {
    public:
        /* =======================================================
            DEBUG MESSENGER
           =======================================================*/
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

        /*  ===========================================================
            PHYSICAL DEVICE
            =========================================================== */
        static std::vector<VkPhysicalDevice> GetAvailableDevices(VkInstance instance);
        static VkPhysicalDeviceProperties GetPhysicalDeviceCapabilities(VkPhysicalDevice device);
        static bool IsPhysicalDeviceSuitable(VulkanPhysicalDevice &device, VkSurfaceKHR surface);

        /*  ============================================================
            LOGICAL DEVICE (VkDevice) 
            ============================================================*/
        static VkDeviceQueueCreateInfo DeviceQueueCreateInfo(
            VkDeviceQueueCreateFlags flags,
            const void *pNext,
            const float *priorities,
            uint32_t queueCount,
            uint32_t queueFamilyIndex
        );

    private:
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallbackDefault(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
    };
}

#endif