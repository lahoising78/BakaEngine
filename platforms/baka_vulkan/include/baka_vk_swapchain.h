#ifndef _BAKA_VK_SWAPCHAIN_H_
#define _BAKA_VK_SWAPCHAIN_H_

#include <vector>
#include <vulkan/vulkan.h>
#include "baka_vk_utils.h"

namespace baka
{
    class VulkanSwapchain
    {
    public:
        VulkanSwapchain();
        VulkanSwapchain(VkPhysicalDevice device, VkSurfaceKHR surface);

    public:
        VkPhysicalDevice gpu;
        VkSurfaceKHR surface;
        SwapchainSupport support;
    };
} // namespace baka


#endif