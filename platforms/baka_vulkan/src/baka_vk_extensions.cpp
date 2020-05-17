#include "baka_logger.h"
#include "baka_vk_extensions.h"
#include <unordered_map>
#include <cstring>

namespace baka
{

    void VulkanExtensions::Init()
    {
        unsigned int extCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, NULL);
        extensions.resize(extCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extensions.data());
    }

    bool VulkanExtensions::EnableExtension(const char *extensionName)
    {
        for(auto &ext : extensions)
        {
            if( strcmp(ext.extensionName, extensionName) == 0 )
            {
                enabled.push_back(ext.extensionName);
                bakalog("Enable extension %s", *(enabled.end()-1));
                return true;
            }
        }

        return false;
    }

    uint32_t VulkanExtensions::EnableExtensions(std::vector<const char *> names)
    {
        uint32_t count = 0;

        uint32_t i;
        for(i = 0; i < names.size(); i++)
        {
            if( EnableExtension(names[i]) )
            {
                count++;
            }
        }

        return count;
    }


}