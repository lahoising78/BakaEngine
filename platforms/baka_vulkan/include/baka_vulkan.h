#ifndef _BAKA_VULKAN_H_
#define _BAKA_VULKAN_H_

#include "baka_platform.h"
#include <vulkan/vulkan.h>
#include "baka_vk_extensions.h"

namespace baka
{
    #ifdef VULKAN_AVAILABLE

    class VulkanGraphics
    {
    public:
        VulkanGraphics(const char *applicationName);
        virtual ~VulkanGraphics();
        virtual void Init();

    private:
        virtual void CreateInstance();

    protected:
        char applicationName[4096];
        VulkanExtensions extensions;

        /* VULKAN STUFF */
        VkInstance instance;
    };

    #else

    BAKA_PLATFORM_NOT_FOUND(VulkanGraphics)

    #endif
}

#endif