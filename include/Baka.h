#ifndef _BAKA_CORE_H_
#define _BAKA_CORE_H_

#include "baka_vk/vulkan.h"
#include "baka_gl/gl.h"

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