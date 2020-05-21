#ifndef _BAKA_VK_EXTENSIONS_
#define _BAKA_VK_EXTENSIONS_

#include <vector>
#include <set>
#include <vulkan/vulkan.h>

namespace baka
{
    class VulkanExtensions
    {
    public:
        virtual void Init() = 0;
        bool EnableExtension(const char *extensionName);
        uint32_t EnableExtensions(std::vector<const char *> names);
        uint32_t EnableAll();

    public:
        std::vector<VkExtensionProperties> extensions;
        std::vector<const char *> enabled;
    };

    class VulkanInstanceExtensions : public VulkanExtensions
    {
    public:
        void Init() override;
    };

    class VulkanDeviceExtensions : public VulkanExtensions
    {
    public:
        void Init();
        void Init(VkPhysicalDevice);
    };
}

#endif