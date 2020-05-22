#include "baka_vk_swapchain.h"

namespace baka
{
    VulkanSwapchain::VulkanSwapchain()
    {
        this->support = {};
        this->surface = VK_NULL_HANDLE;
    }

    VulkanSwapchain::VulkanSwapchain(VkPhysicalDevice gpu, VkSurfaceKHR surface)
    {
        this->surface = surface;
        this->gpu = gpu;
        this->support = VulkanUtils::GetSwapchainSwpport(gpu, surface);
    }
} // namespace baka
