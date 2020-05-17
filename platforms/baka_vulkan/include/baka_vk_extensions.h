#ifndef _BAKA_VK_EXTENSIONS_
#define _BAKA_VK_EXTENSIONS_

#include <vector>
#include <vulkan/vulkan.h>

namespace baka
{
    class VulkanExtensions
    {
    public:
        void Init();
        bool EnableExtension(const char *extensionName);
        uint32_t EnableExtensions(std::vector<const char *> names);

    public:
        std::vector<VkExtensionProperties> extensions;
        std::vector<const char *> enabled;
    };
}

#endif