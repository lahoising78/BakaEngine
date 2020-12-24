#ifndef _BAKA_LIGHTS_H_
#define _BAKA_LIGHTS_H_

#include <glm/glm.hpp>
#include <baka_shader.h>

#define DIR_LIGHT_MAX_NAME 64

namespace baka
{

class Light
{
public:
    Light();
    Light(glm::vec3 color, float intensity) 
    {
        this->color = color;
        this->intensity = intensity;
    }

    virtual void Bind(Shader *shader, const char *uniformName) = 0;

protected:
    static void BindBaseLight(Light *light, Shader *shader, const char *uniformName);

public:
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    float intensity = 1.0f;
// create
// destroy
};

} // namespace baka

#endif