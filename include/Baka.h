#ifndef _BAKA_CORE_H_
#define _BAKA_CORE_H_

#ifdef VULKAN_AVAILABLE
#include "baka_vulkan.h"
#endif

class BakaApplication
{
public:
    ~BakaApplication();
    int Main(int argc, char *argv[]);
    void Update(float deltaTime);

public:
    #ifdef VULKAN_AVAILABLE
    baka::VulkanGraphics *vk_graphics;
    #endif
};

#endif