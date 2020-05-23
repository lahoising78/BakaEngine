#include <cstring>
#include "baka_logger.h"
#include "baka_vk_swapchain.h"
#include "baka_graphics.h"

namespace baka
{
    VulkanSwapchain::VulkanSwapchain()
    {
        std::memset(this, 0, sizeof(VulkanSwapchain));
    }

    VulkanSwapchain::VulkanSwapchain(VkPhysicalDevice gpu, VkSurfaceKHR surface)
    {
        this->surface = surface;
        this->gpu = gpu;
        VulkanUtils::GetSwapchainSupport(&this->support, gpu, surface);

        bakalog("support sizes: %u %u", this->support.formats.size(), this->support.presentModes.size());
    }

    VulkanSwapchain::~VulkanSwapchain()
    {

    }

    void VulkanSwapchain::Create()
    {
        bakalog("creating swapchain");
        VulkanUtils::GetSwapchainSupport(&this->support, this->gpu, this->surface);
        VkSurfaceFormatKHR format = {};
        
        if(!this->choose_surface_format)
        {
            this->choose_surface_format = VulkanSwapchain::ChooseSurfaceFormatDefault;
        }

        bakalog("choose surface format from %u", this->support.formats.size());
        format = this->choose_surface_format(
            this->support.formats.data(), 
            this->support.formats.size(),
            VkFormat::VK_FORMAT_B8G8R8A8_SRGB,
            VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
        );
        bakalog("format %d, color space %d", format.format, format.colorSpace);

        if(!this->choose_present_mode)
        {
            this->choose_present_mode = VulkanSwapchain::ChoosePresentMode;
        }

        bakalog("choose present mode from %u", this->support.presentModes.size());
        VkPresentModeKHR mode = this->choose_present_mode(
            this->support.presentModes.data(),
            this->support.presentModes.size(),
            VK_PRESENT_MODE_MAILBOX_KHR
        );

        bakalog("present mode %d", mode);

        VkExtent2D ext = VulkanSwapchain::ChooseSwapExtent(&this->support.capabilities);
    }

    VkSurfaceFormatKHR VulkanSwapchain::ChooseSurfaceFormatDefault(
        const VkSurfaceFormatKHR *surfaceFormats, 
        uint32_t surfaceFormatCount,
        VkFormat preferedFormat,
        VkColorSpaceKHR preferedColorSpace)
    {
        VkSurfaceFormatKHR format = {};
        int i = 0;
        
        if(!surfaceFormats) return {};

        for(i = 0; i < surfaceFormatCount; i++)
        {
            format = surfaceFormats[i];
            if( format.colorSpace == preferedColorSpace && 
                format.format == preferedFormat )
            {
                return format;
            }
        }

        return surfaceFormats[0];
    }

    /*  The present mode is what determines how the images in the swapchain are going to be presented.
        There are a couple of modes, like:
            VK_PRESENT_MODE_FIFO_KHR
            VK_PRESENT_MODE_MAILBOX_KHR 
            
        The first one says that images should be present in an order of first in first out. It works like a queue, 
        but the problem is that the program has to wait if the queue is full.
        The second one is another version of the fist mode. The difference is that, once the queue is full, the 
        old images will simply will replaced with the new ones, intead of waiting for the old ones to be rendered.
        
        Mailbox is the only mode that is guaranteed to be supported. 
        
        There are other present modes, and you can read about them from here:
            https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain*/
    VkPresentModeKHR VulkanSwapchain::ChoosePresentMode(const VkPresentModeKHR *modes, uint32_t modeCount, VkPresentModeKHR preferedMode)
    {
        VkPresentModeKHR presentMode = {};

        uint32_t i = 0;
        for(i = 0; i < modeCount; i++)
        {
            presentMode = modes[i];
            if(presentMode == preferedMode) return presentMode;
        }

        return VK_PRESENT_MODE_MAILBOX_KHR;
    }

    /*  having extent of uint32_max means that we can differ between the extent of the window and the resolution of the surface.
        This is determined by the window manager.  */
    VkExtent2D VulkanSwapchain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR *capabilities)
    {
        VkExtent2D actualExtent = { (uint32_t)Graphics::GetWidth(), (uint32_t)Graphics::GetHeight() };
        if(!capabilities) return {UINT32_MAX, UINT32_MAX};

        if(capabilities->currentExtent.width != UINT32_MAX)
        {
            return capabilities->currentExtent;
        }
        
        actualExtent.width = std::max(
            capabilities->minImageExtent.width, 
            std::min(capabilities->maxImageExtent.width, actualExtent.width)
        );

        actualExtent.height = std::max(
            capabilities->minImageExtent.height,
            std::min(capabilities->maxImageExtent.height, actualExtent.height)
        );

        return actualExtent;
    }
} // namespace baka
