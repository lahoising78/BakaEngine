#ifndef _BAKA_SHADER_H_
#define _BAKA_SHADER_H_

#include <baka_path_explorer.h>

namespace baka
{
    class Shader
    {
    public:
        typedef enum
        {
            NONE = 0,
            FLOAT,
            FLOAT2,
            FLOAT3,
            FLOAT4,
            MAT4X4
        } Type;

    public:
        static Shader *Create(const char *vertSrc, const char *fragSrc);
        static Shader *Load(const char *vertPath, const char *fragPath, ResourceType resourceType = ResourceType::ASSET);
        
        virtual ~Shader() {}
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Destroy() = 0;
        virtual void SetUniform(Shader::Type shaderType, const char *name, void *data) = 0;
    };
} // namespace baka


#endif