#ifndef _BAKA_LIGHTS_H_
#define _BAKA_LIGHTS_H_

#include <glm/glm.hpp>

namespace baka
{

class Light
{
public:
    Light();
    Light(glm::vec4 color, float intensity) 
    {
        this->color = color;
        this->intensity = intensity;
    }

public:
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    float intensity = 1.0f;
// create
// destroy
};

} // namespace baka

#endif