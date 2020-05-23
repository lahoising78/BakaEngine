#include <cstring>
#include <SDL_vulkan.h>
//#include <SDL2/SDL_vulkan.h>
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
        this->swapchain = VulkanSwapchain();
    }

    VulkanGraphics::~VulkanGraphics()
    {
        vkDestroySwapchainKHR(this->logicalDevice.device, this->swapchain.swapchain, nullptr);
        vkDestroyDevice(this->logicalDevice.device, NULL);
        vkDestroySurfaceKHR(this->instance, this->surface, NULL);
        if(enableValidations) VulkanValidation::DestroyDebugMessenger(this->instance);
        vkDestroyInstance(this->instance, NULL);

        bakalog("VulkanGraphics closed");
    }

    void VulkanGraphics::Init()
    {
        this->CreateInstance();
        
        if(enableValidations) VulkanValidation::SetupDebugMessenger(this->instance);
        
        this->CreateSurface();
        this->PickPhysicalDevice();
        
        if(this->physicalDevice.device == VK_NULL_HANDLE) return;
        
        this->CreateLogicalDevice();
        this->swapchain.Create();

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
        instance_extensions.Init();
        unsigned int extCount = 0;
        /* We query the number of extensions that sdl needs from vulkan */
        SDL_Vulkan_GetInstanceExtensions(baka::Graphics::GetWindow(), &extCount, NULL);
        /* buffer our holder with the necessary amount */
        std::vector<const char *> sdlExts(extCount);
        /* query the actual extension names */
        SDL_Vulkan_GetInstanceExtensions(baka::Graphics::GetWindow(), &extCount, sdlExts.data());
        /* the way I set this up is to enable all the extensions that instance_extensions.enabled contains */
        instance_extensions.EnableExtensions(sdlExts);
        // instance_extensions.EnableAll();
        
        /* this is an extension we need to create a debug messenger on vulkan. See VulkanValidation::SetupDebugMessenger */
        if(enableValidations)
        {
            instance_extensions.EnableExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        instanceInfo.enabledExtensionCount = static_cast<uint32_t>(instance_extensions.enabled.size());
        instanceInfo.ppEnabledExtensionNames = instance_extensions.enabled.data();

        VkDebugUtilsMessengerCreateInfoEXT debugInfo = {};
        if( enableValidations )
        {
            instance_layers.Init();
            instance_layers.EnableLayers({
                "VK_LAYER_KHRONOS_validation"
                // , 
                // "VK_LAYER_LUNARG_standard_validation"
                , "VK_LAYER_LUNARG_api_dump"
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

    void VulkanGraphics::CreateSurface()
    {
        bool surfaceCreate = SDL_Vulkan_CreateSurface(baka::Graphics::GetWindow(), this->instance, &this->surface);
        if(!surfaceCreate)
        {
            bakawarn("surface creation failed: %s", SDL_GetError());
            return;
        }
    }
    
    void VulkanGraphics::PickPhysicalDevice()
    {
        auto availablePhysicalDevices = VulkanUtils::GetAvailableDevices(this->instance);
        if(availablePhysicalDevices.size() < 1) return;
        
        // std::vector<const char *> requiredExtensions = this->instance_extensions.enabled;
        for(auto phys : availablePhysicalDevices)
        {
            VulkanPhysicalDevice vpd = VulkanPhysicalDevice(phys);

            // if(this->swapchain) delete this->swapchain;
            this->swapchain.support = {};
            VulkanUtils::GetSwapchainSupport(&this->swapchain.support, phys, this->surface);
            
            if( vpd.IsSuitable(&this->swapchain, this->surface, {VK_KHR_SWAPCHAIN_EXTENSION_NAME}) )
            {
                this->physicalDevice = vpd;
                bakalog("Choosing physical device: %s", vpd.properties.deviceName);
                this->swapchain.physicalDevice = &this->physicalDevice;
                this->swapchain.surface = this->surface;
                // this->swapchain.Create();
                // this->physicalDevice.extensions.EnableAll();
                break;
            }
        }

        if(this->physicalDevice.device == VK_NULL_HANDLE)
        {
            bakawarn("There are no suitable physical devices");
        }
    }

    void VulkanGraphics::CreateLogicalDevice()
    {
        this->logicalDevice = {};
        this->logicalDevice.physicalDevice = &this->physicalDevice;

        std::vector<float> priorities = {1.0f};
        std::vector<VkDeviceQueueCreateInfo> queueInfos; 
        
        for(auto familyIndex : this->logicalDevice.physicalDevice->queues.familyIndices)
        {
            queueInfos.push_back(VulkanUtils::DeviceQueueCreateInfo(
                0, nullptr,
                priorities.data(),
                static_cast<uint32_t>(priorities.size()),
                familyIndex.second
            ));
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};
        VkDeviceCreateInfo deviceInfo = {};
        deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceInfo.pQueueCreateInfos = queueInfos.data();
        deviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
        deviceInfo.pEnabledFeatures = &deviceFeatures;
        deviceInfo.enabledExtensionCount = static_cast<uint32_t>(this->logicalDevice.physicalDevice->extensions.enabled.size());
        deviceInfo.ppEnabledExtensionNames = this->logicalDevice.physicalDevice->extensions.enabled.data();
        
        if(enableValidations)
        {
            bakalog("enabled extension count: %u", this->logicalDevice.physicalDevice->extensions.enabled.size());
            for(auto ext : this->logicalDevice.physicalDevice->extensions.enabled)
                bakalog("\t%s", ext);
            deviceInfo.enabledLayerCount = static_cast<uint32_t>(instance_layers.enabled.size());
            deviceInfo.ppEnabledLayerNames = instance_layers.enabled.data();
        }

        VkResult res = vkCreateDevice(this->logicalDevice.physicalDevice->device, &deviceInfo, NULL, &this->logicalDevice.device);
        if(res != VK_SUCCESS)
        {
            bakawarn("Device creation failed with error code %d", res);
        }

        this->logicalDevice.queues[VK_QUEUE_GRAPHICS_BIT] = VulkanLogicalDeviceQueues(
            this->logicalDevice.device, 
            this->physicalDevice.queues.familyIndices[VK_QUEUE_GRAPHICS_BIT],
            0
        );

        this->logicalDevice.queues[VkQueueFlagBits::VK_QUEUE_FLAG_BITS_MAX_ENUM] = VulkanLogicalDeviceQueues(
            this->logicalDevice.device,
            this->physicalDevice.queues.familyIndices[VkQueueFlagBits::VK_QUEUE_FLAG_BITS_MAX_ENUM],
            0
        );

        this->swapchain.logicalDevice = &this->logicalDevice;
    }

    #endif
} // namespace baka

