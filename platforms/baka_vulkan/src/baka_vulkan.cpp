#include <cstring>
#include <SDL2/SDL_vulkan.h>
#include "baka_logger.h"
#include "baka_vulkan.h"
#include "baka_vk_utils.h"
#include "baka_graphics.h"

namespace baka
{
    #ifdef VULKAN_AVAILABLE

    VulkanGraphics::VulkanGraphics(const char *applicationName, bool enableValidations)
    {
        bakalog("Hello from VulkanGraphics");
        strcpy(this->applicationName, applicationName);
        this->enableValidations = enableValidations;
    }

    VulkanGraphics::~VulkanGraphics()
    {
        bakalog("VulkanGraphics closing");

        if(enableValidations) VulkanValidation::DestroyDebugMessenger(this->instance);
        vkDestroyInstance(this->instance, NULL);
    }

    void VulkanGraphics::Init()
    {
        this->CreateInstance();
        if(enableValidations) VulkanValidation::SetupDebugMessenger(this->instance);
        this->PickPhysicalDevice();
    }

    void VulkanGraphics::CreateInstance()
    {
        /* Just some information about the application */
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = applicationName;
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.pEngineName = "Baka Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.apiVersion = VK_API_VERSION_1_1;

        /* The VkInstance is an instance of vulkan itself in the application */
        VkInstanceCreateInfo instanceInfo = {};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfo;

        /* Vulkan works mostly with extensions. In this block we query the extensions
        that sdl needs to run vulkan on a window, using a common pattern used in vulkan. */
        extensions.Init();
        unsigned int extCount = 0;
        /* We query the number of extensions that sdl needs from vulkan */
        SDL_Vulkan_GetInstanceExtensions(baka::Graphics::GetWindow(), &extCount, NULL);
        /* buffer our holder with the necessary amount */
        std::vector<const char *> sdlExts(extCount);
        /* query the actual extension names */
        SDL_Vulkan_GetInstanceExtensions(baka::Graphics::GetWindow(), &extCount, sdlExts.data());
        /* the way I set this up is to enable all the extensions that instance_extensions.enabled contains */
        extensions.EnableExtensions(sdlExts);
        
        /* this is an extension we need to create a debug messenger on vulkan. See VulkanValidation::SetupDebugMessenger */
        if(enableValidations)
            extensions.EnableExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        instanceInfo.enabledExtensionCount = extensions.enabled.size();
        instanceInfo.ppEnabledExtensionNames = extensions.enabled.data();

        VkDebugUtilsMessengerCreateInfoEXT debugInfo = {};
        if( enableValidations )
        {
            instance_layers.Init();
            instance_layers.EnableLayers({
                "VK_LAYER_KHRONOS_validation",
                "VK_LAYER_LUNARG_standard_validation"
            });

            instanceInfo.enabledLayerCount = (uint32_t)instance_layers.enabled.size();
            instanceInfo.ppEnabledLayerNames = instance_layers.enabled.data();

            debugInfo = VulkanUtils::DebugMessengerCreateInfoDefault();
            instanceInfo.pNext = &debugInfo;
        }

        VkResult res = vkCreateInstance(&instanceInfo, NULL, &this->instance);
        if(res != VK_SUCCESS)
        {
            bakawarn("VkInstance create failed with code %d", res);
        }
    }
    
    void VulkanGraphics::PickPhysicalDevice()
    {
        auto availablePhysicalDevices = VulkanUtils::GetAvailableDevices(this->instance);
        if(availablePhysicalDevices.size() < 1) return;
        
        for(auto phys : availablePhysicalDevices)
        {
            VulkanPhysicalDevice vpd = VulkanPhysicalDevice(phys);
            if( VulkanUtils::IsPhysicalDeviceSuitable(vpd) )
            {
                this->physicalDevice = vpd;
                bakalog("Choosing physical device: %s", vpd.properties.deviceName);
                break;
            }
        }
    }

    #endif
} // namespace baka

