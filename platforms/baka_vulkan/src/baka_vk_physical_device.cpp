#ifdef VULKAN_AVAILABLE

#include "baka_vk_physical_device.h"
#include "baka_vk_swapchain.h"

namespace baka
{
    VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device)
        : VulkanPhysicalDevice()
    {
        if(device == VK_NULL_HANDLE) return;

        this->device = device;
        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);

        queues = VulkanPhysicalDeviceQueues(this->device);
        this->extensions.Init(this->device);
    }

    bool VulkanPhysicalDevice::IsSuitable(VulkanSwapchain *swapchain, VkSurfaceKHR surface, std::vector<const char *> requiredExtensions)
    {
        if(!swapchain) return false;

        /* are we a discrete gpu? */
        // if( this->properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ) return false;

        /* do we have a graphics queue? */
        if( !this->queues.FindQueueIndex( VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT ) ) return false;

        /* do we support presenting to the surface? */
        if( !this->queues.FindPresentQueue(surface) ) return false;
        
        /* do we support the necessary extensions? */
        this->extensions.EnableExtensions(requiredExtensions);
        if( this->extensions.enabled.size() != requiredExtensions.size() ) return false;

        if( swapchain->support.formats.empty() || swapchain->support.presentModes.empty() ) return false;
        
        return true;
    }

    bool FeatureContains(VkPhysicalDeviceFeatures container, VkPhysicalDeviceFeatures check)
    {
        if( check.alphaToOne && !(container.alphaToOne & check.alphaToOne) ) return false;
        if( check.depthBiasClamp && !(container.depthBiasClamp & check.alphaToOne) ) return false;
        if( check.depthBounds && !(container.depthBounds & check.depthBounds) ) return false;
        if( check.depthClamp && !(container.depthClamp & check.depthClamp)) return false;
        if(check.drawIndirectFirstInstance && !(container.drawIndirectFirstInstance & check.drawIndirectFirstInstance)) return false;
        if(check.dualSrcBlend && !(container.dualSrcBlend & check.dualSrcBlend)) return false;
        if(check.fillModeNonSolid && !(container.fillModeNonSolid & check.fillModeNonSolid)) return false;
        if(check.fragmentStoresAndAtomics && !(container.fragmentStoresAndAtomics & check.fragmentStoresAndAtomics)) return false;
        if(check.fullDrawIndexUint32 && !(container.fullDrawIndexUint32 & check.fullDrawIndexUint32)) return false;
        if(check.geometryShader && !(container.geometryShader & check.geometryShader)) return false;
        if(check.imageCubeArray && !(container.imageCubeArray & check.imageCubeArray)) return false;
        if(check.independentBlend && !(container.independentBlend & check.independentBlend)) return false;
        if(check.inheritedQueries && !(container.inheritedQueries & check.inheritedQueries)) return false;
        if(check.largePoints && !(container.largePoints & check.largePoints)) return false;
        if(check.logicOp && !(container.logicOp & check.logicOp)) return false;
        if(check.multiDrawIndirect && !(container.multiDrawIndirect & check.multiDrawIndirect)) return false;
        if(check.multiViewport && !(container.multiViewport & check.multiViewport)) return false;
        if(check.occlusionQueryPrecise && !(container.occlusionQueryPrecise & check.occlusionQueryPrecise)) return false;
        if(check.pipelineStatisticsQuery && !(container.pipelineStatisticsQuery & check.pipelineStatisticsQuery)) return false;
        if(check.robustBufferAccess && !(container.robustBufferAccess & check.robustBufferAccess)) return false;
        if(check.samplerAnisotropy && !(container.samplerAnisotropy & check.samplerAnisotropy)) return false;
        if(check.sampleRateShading && !(container.sampleRateShading & check.sampleRateShading)) return false;
        if(check.shaderClipDistance && !(container.shaderClipDistance & check.shaderClipDistance)) return false;

        return true;
    }
}

#endif