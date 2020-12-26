#ifndef _BAKA_LIGHTS_LIGHT_H_
#define _BAKA_LIGHTS_LIGHT_H_

#include <glm/glm.hpp>
#include <baka_shader.h>

#define DIR_LIGHT_MAX_NAME 64

namespace baka
{

class Light
{
public:
    enum Type
    {
        AMBIENT = 0,
        DIRECTIONAL,
        POINT
    };

public:
    Light();
    Light(glm::vec3 color, float intensity, Type type) 
    {
        this->color = color;
        this->intensity = intensity;
        this->type = type;
    }

    virtual void Bind(Shader *shader, const char *uniformName) = 0;
    Type GetType() { return this->type; }

protected:
    static void BindBaseLight(Light *light, Shader *shader, const char *uniformName);

public:
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    float intensity = 1.0f;
    Type type;
};

} // namespace baka

#endif