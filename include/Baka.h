#ifndef _BAKA_CORE_H_
#define _BAKA_CORE_H_

#include "baka_vulkan.h"
#include "baka_open_gl.h"

class BakaApplication
{
public:
    ~BakaApplication();
    int Main(int argc, char *argv[]);
    void Update(float deltaTime);

public:
    baka::VulkanGraphics *vk_graphics;
    baka::GLGraphics *gl_graphics;
};

#endif