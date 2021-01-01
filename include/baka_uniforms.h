#ifndef _BAKA_UNIFORMS_H_
#define _BAKA_UNIFORMS_H_

#include <cstddef>
#include <glm/glm.hpp>

namespace baka
{
    typedef enum
    {
        UNIFORM_NONE = 0,
        UNIFORM_FLOAT,
        UNIFORM_FLOAT2,
        UNIFORM_FLOAT3,
        UNIFORM_FLOAT4,
        UNIFORM_MAT4X4,
        UNIFORM_SAMPLER2D
    } UniformType;

    typedef union UniformValue_u
    {
        glm::mat4   uMat4;
        glm::vec4   uVec4;
        glm::vec3   uVec3;
        glm::vec2   uVec2;
        float       uFloat;

        UniformValue_u(glm::mat4 val) { this->uMat4   = val; }
        UniformValue_u(glm::vec4 val) { this->uVec4   = val; }
        UniformValue_u(glm::vec3 val) { this->uVec3   = val; }
        UniformValue_u(glm::vec2 val) { this->uVec2   = val; }
        UniformValue_u(float val)     { this->uFloat  = val; }
    } UniformValue;

    static std::size_t GetUniformSize(UniformType type)
    {
        switch(type)
        {
        case UniformType::UNIFORM_FLOAT4:       return sizeof(float) * 4;
        case UniformType::UNIFORM_FLOAT3:       return sizeof(float) * 3;
        case UniformType::UNIFORM_FLOAT2:       return sizeof(float) * 2;
        case UniformType::UNIFORM_FLOAT:        return sizeof(float);
        case UniformType::UNIFORM_MAT4X4:       return sizeof(glm::mat4);
        case UniformType::UNIFORM_SAMPLER2D:    return sizeof(void*);
        default: return 0;
        }
    }
} // namespace baka

#endif