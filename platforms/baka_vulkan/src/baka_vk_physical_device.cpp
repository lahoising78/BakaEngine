#include "baka_vk_physical_device.h"

namespace baka
{
    VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device, std::vector<VkPhysicalDeviceFeatures> requiredFeatures)
    {
        if(device == VK_NULL_HANDLE) return;

        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);
        this->device = device;
        this->requiredFeatures = requiredFeatures;

        queues = VulkanPhysicalDeviceQueues(this->device);
    }

    bool VulkanPhysicalDevice::IsSuitable()
    {
        if( this->properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ) return false;

        if( !this->queues.FindQueueIndex( VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT ) ) return false;

        // for(VkPhysicalDeviceFeatures f : requiredFeatures)
        // {
        //     if( !FeatureContains(this->features, f) ) return false;
        // }
        
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