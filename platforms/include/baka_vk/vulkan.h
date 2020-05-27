#ifndef _BAKA_VULKAN_H_
#define _BAKA_VULKAN_H_

#include "baka_platform.h"

namespace baka
{
    #ifdef VULKAN_AVAILABLE
    class VulkanGraphics
    {
    public:
        VulkanGraphics();
        ~VulkanGraphics();
        virtual void Init();
    };
    #else
    BAKA_PLATFORM_NOT_FOUND(VulkanGraphics)
    #endif

} // namespace baka


#endif