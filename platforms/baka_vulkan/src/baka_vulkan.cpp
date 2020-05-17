#include "baka_logger.h"
#include "baka_vulkan.h"
#include "baka_graphics.h"
#include <cstring>
#include <SDL2/SDL_vulkan.h>

namespace baka
{
    #ifdef VULKAN_AVAILABLE

    VulkanGraphics::VulkanGraphics(const char *applicationName)
    {
        bakalog("Hello from VulkanGraphics");
        strcpy(this->applicationName, applicationName);
    }

    VulkanGraphics::~VulkanGraphics()
    {
        bakalog("VulkanGraphics closing");

        vkDestroyInstance(this->instance, NULL);
    }

    void VulkanGraphics::Init()
    {
        this->CreateInstance();
    }

    void VulkanGraphics::CreateInstance()
    {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = applicationName;
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.pEngineName = "Baka Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.apiVersion = VK_API_VERSION_1_1;

        VkInstanceCreateInfo instanceInfo = {};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfo;

        unsigned int extCount = 0;
        SDL_Vulkan_GetInstanceExtensions(baka::Graphics::GetWindow(), &extCount, NULL);
        extensions.extensions.resize(extCount);
        extensions.names.resize(extCount);
        SDL_Vulkan_GetInstanceExtensions(baka::Graphics::GetWindow(), &extCount, extensions.names.data());
        
        instanceInfo.enabledExtensionCount = extCount;
        instanceInfo.ppEnabledExtensionNames = extensions.names.data();

        instanceInfo.enabledLayerCount = 0;

        VkResult res = vkCreateInstance(&instanceInfo, NULL, &this->instance);
        if(res)
        {
            bakawarn("VkInstance create failed with code %u", res);
        }
    }
    
    #endif
} // namespace baka

