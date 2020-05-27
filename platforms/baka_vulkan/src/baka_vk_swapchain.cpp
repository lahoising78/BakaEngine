#ifdef VULKAN_AVAILABLE

#include <cstring>
#include "baka_logger.h"
#include "baka_vk_swapchain.h"
#include "baka_graphics.h"
// #include "baka_vk_device.h"

namespace baka
{
    VulkanSwapchain::VulkanSwapchain()
    {
        std::memset(this, 0, sizeof(VulkanSwapchain));
    }

    // VulkanSwapchain::VulkanSwapchain(VkPhysicalDevice gpu, VkSurfaceKHR surface)
    // {
    //     this->surface = surface;
    //     this->gpu = gpu;
    //     VulkanUtils::GetSwapchainSupport(&this->support, gpu, surface);

    //     bakalog("support sizes: %u %u", this->support.formats.size(), this->support.presentModes.size());
    // }

    VulkanSwapchain::~VulkanSwapchain()
    {

    }

    void VulkanSwapchain::Create()
    {
        bakalog("creating swapchain");
        VulkanUtils::GetSwapchainSupport(&this->support, this->physicalDevice->device, this->surface);
        VkSurfaceFormatKHR format = {};
        
        if(!this->choose_surface_format)
        {
            this->choose_surface_format = VulkanSwapchain::ChooseSurfaceFormatDefault;
        }

        format = this->choose_surface_format(
            this->support.formats.data(), 
            this->support.formats.size(),
            VkFormat::VK_FORMAT_B8G8R8A8_SRGB,
            VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
        );

        if(!this->choose_present_mode)
        {
            this->choose_present_mode = VulkanSwapchain::ChoosePresentMode;
        }

        VkPresentModeKHR mode = this->choose_present_mode(
            this->support.presentModes.data(),
            this->support.presentModes.size(),
            VK_PRESENT_MODE_MAILBOX_KHR
        );

        VkExtent2D ext = VulkanSwapchain::ChooseSwapExtent(&this->support.capabilities);
        ext = {0,0};

        /*  This is how many buffers we will have (image buffer).
            It is recommended to use the min possible + 1 */
        uint32_t imageCount = this->support.capabilities.minImageCount + 1;
        
        /*  make sure we don't use more than we actually can.
            note that a maxImageCount of 0 means we can have as many as we want. */
        if (this->support.capabilities.maxImageCount > 0 && imageCount > this->support.capabilities.maxImageCount) {
            imageCount = this->support.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = this->surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = format.format;
        createInfo.imageColorSpace = format.colorSpace;
        createInfo.imageExtent = ext;

        /* how many layers each image has. 
        always 1, unless we are creating a stereoscopic 3D app  */
        createInfo.imageArrayLayers = 1;

        /* specify what kind of operations we are going to do.
        since we are drawing directly to it, we use color attachment bit
        we can also use transfer dst if we plan to do post-processing */
        createInfo.imageUsage = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        /* now we specify how we are going to use our swap chain images.
        Since we are going to write to them using graphics queue, and then
        presenting them using presentation queue, we specify those. 
        The following procdure can be found here:
            https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain*/
        uint32_t famIndices[] = {
            this->physicalDevice->queues.familyIndices[ VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT ],
            this->physicalDevice->queues.familyIndices[ VkQueueFlagBits::VK_QUEUE_FLAG_BITS_MAX_ENUM ]
        };

        /** @note there is a chance we are going to use the same queues for both of these
         * operations, so we need to handle that situation. 
         */
        if( famIndices[0] != famIndices[1] )
        {
            /* concurrent mode means the image can be used across multiple queues */
            createInfo.imageSharingMode = VkSharingMode::VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = famIndices;
        }
        else
        {
            createInfo.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }
        
        /* we can apply a transform to the image, like rotating 90 degrees clockwise or something.
        We don't want to do that, so just specify current transform */
        createInfo.preTransform = this->support.capabilities.currentTransform;
        /* don't blend with other windows */
        createInfo.compositeAlpha = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        createInfo.presentMode = mode;
        
        /* don't bother calculating a pixel if you can't see it anyway (like a window in front of it) */
        createInfo.clipped = VK_TRUE;

        /* needs to be specified if you are creating a new swapchain from another */
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult res = vkCreateSwapchainKHR(this->logicalDevice->device, &createInfo, nullptr, &this->swapchain);
        if(res != VK_SUCCESS)
        {
            bakawarn("Swapchain creation failed with error code %d", res);
        }
        // VKASSERT(res, vkCreateSwapchainKHR(this->logicalDevice->device, &createInfo, nullptr, &this->swapchain), "Swapchain creation")
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
        
        fifo is the only mode that is guaranteed to be supported. 
        
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

        return VK_PRESENT_MODE_FIFO_KHR;
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

#endif