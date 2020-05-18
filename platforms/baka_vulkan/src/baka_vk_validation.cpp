#include <cstring>
#include <algorithm>
#include "baka_logger.h"
#include "baka_vk_validation.h"
#include "baka_vk_utils.h"

namespace baka
{
    typedef struct
    {
        VkDebugUtilsMessengerEXT debugMessenger;
    } VulkanValidationManager;

    static VulkanValidationManager validation_manager = {};

    void VulkanValidation::Init()
    {
        unsigned int count = 0;
        vkEnumerateInstanceLayerProperties(&count, nullptr);
        layers.resize(count);
        vkEnumerateInstanceLayerProperties(&count, layers.data());
    }

    bool VulkanValidation::EnableLayer(const char *layer)
    {

        for(auto &l : this->layers)
        {
            if(strcmp( layer, l.layerName ) == 0)
            {
                if(std::find(this->enabled.begin(), this->enabled.end(), l.layerName) != this->enabled.end())
                {
                    bakalog("%s has already been enabled", layer);
                    return false;
                }
                enabled.push_back(l.layerName);
                bakalog("Enable validation layer %s", *(enabled.end()-1));
                return true;
            }
        }

        return false;
    }

    uint32_t VulkanValidation::EnableLayers(std::vector<const char *> layers)
    {
        uint32_t count = 0;

        uint32_t i;
        for(i = 0; i < layers.size(); i++)
        {
            if( EnableLayer( layers[i] ) )
            {
                count++;
            }
        }

        return count;
    }

    uint32_t VulkanValidation::EnableAllAvailable()
    {
        uint32_t count = 0;
        bakalog("Enable all validation");
        for(auto &l : this->layers)
        {
            enabled.push_back(l.layerName);
            bakalog("\t%s", *(enabled.end()-1));
            count++;
        }
        return count;
    }

    void VulkanValidation::DisableLayer(const char *layer)
    {
        for(auto it = this->enabled.begin(); it != this->enabled.end(); it++)
        {
            if( strcmp(*it, layer) == 0 )
            {
                this->enabled.erase(it);
                bakalog("disable layer %s", layer);
                return;
            }
        }
    }

    void VulkanValidation::SetupDebugMessenger(VkInstance instance)
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo = VulkanUtils::DebugMessengerCreateInfoDefault();

        VkResult res = VulkanUtils::CreateDebugUtilsMessengerEXT(instance, &createInfo, NULL, &validation_manager.debugMessenger);
        if( res != VK_SUCCESS )
        {
            bakawarn("debug messenger could not be created. Failed with error %d", res);
        }
    }

    void VulkanValidation::DestroyDebugMessenger(VkInstance instance)
    {
        bakalog("Destroy debug messenger");
        VulkanValidation::DestroyDebugUtilsMessengerEXT(instance, validation_manager.debugMessenger, nullptr);
    }

    void VulkanValidation::DestroyDebugUtilsMessengerEXT(
            VkInstance instance, 
            VkDebugUtilsMessengerEXT debugMessenger, 
            const VkAllocationCallbacks* pAllocator) 
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }
    
} // namespace baka
