#ifndef _BAKA_VK_SWAPCHAIN_H_
#define _BAKA_VK_SWAPCHAIN_H_

#include <vector>
#include <vulkan/vulkan.h>
#include "baka_vk_utils.h"

#define BAKA_VK_FORMAT_DEFAULT VK_FORMAT_B8G8R8A8_SRGB
#define BAKA_VK_COLOR_SPACE_DEFAULT VK_COLOR_SPACE_SRGB_NONLINEAR_KHR

namespace baka
{
    class VulkanSwapchain
    {
    public:
        VulkanSwapchain();
        VulkanSwapchain(VkPhysicalDevice device, VkSurfaceKHR surface);
        ~VulkanSwapchain();

        // virtual void Init();

        /* STATIC METHODS */
        static VkSurfaceFormatKHR ChooseSurfaceFormatDefault(
            const VkSurfaceFormatKHR *surfaceFormats, 
            uint32_t surfaceFormatCount,
            VkFormat preferedFormat,
            VkColorSpaceKHR preferedColorSpace);

        static VkPresentModeKHR ChoosePresentMode(
            const VkPresentModeKHR *modes, 
            uint32_t modesCount, 
            VkPresentModeKHR prefered);

        static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR *capabilities);

    public:
        VkSurfaceFormatKHR (*choose_surface_format)(
            const VkSurfaceFormatKHR *surfaceFormats, 
            uint32_t surfaceFormatCount,
            VkFormat preferedFormat,
            VkColorSpaceKHR preferedColorSpace);

        VkPresentModeKHR (*choose_present_mode)(
            const VkPresentModeKHR *modes, 
            uint32_t modesCount, 
            VkPresentModeKHR prefered);

    public:
        VkPhysicalDevice gpu;
        VkSurfaceKHR surface;
        SwapchainSupport support;
    };
} // namespace baka


#endif