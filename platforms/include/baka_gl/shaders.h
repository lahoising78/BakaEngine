#ifndef _BAKA_GL_SHADERS_H_
#define _BAKA_GL_SHADERS_H_

#include <baka_shader.h>

namespace baka
{
    namespace gl
    {
        class Shader : public baka::Shader
        {
        public:
            Shader(const char *vertSrc, const char *fragSource);
            void Destroy() override;
            void Bind() override;

            unsigned int GetRendererId() { return renderer_program_id; };

        private:
            unsigned int CompileShader(unsigned int shaderType, const char *source);

        private:
            unsigned int renderer_program_id;
        };
    }
} // namespace baka


#endif