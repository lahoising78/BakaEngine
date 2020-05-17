#ifndef _BAKA_VK_EXTENSIONS_
#define _BAKA_VK_EXTENSIONS_

#include <vector>
#include <vulkan/vulkan.h>

namespace baka
{
    class VulkanExtensions
    {
    public:
        std::vector<VkExtensionProperties> extensions;
        std::vector<const char *> names;
    };
}

#endif