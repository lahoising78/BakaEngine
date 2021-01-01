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