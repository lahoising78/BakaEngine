#ifndef _BAKA_GL_SHADERS_H_
#define _BAKA_GL_SHADERS_H_

#include <unordered_map>
#include <string>

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

#include <baka_shader.h>

namespace baka
{
    namespace gl
    {
        class Shader : public baka::Shader
        {
        public:
            Shader(const char *vertSrc, const char *fragSource);
            ~Shader();
            void Destroy() override;
            void Bind() override;
            void SetUniform(Shader::Type shaderType, const char *name, void *data) override;

            unsigned int GetRendererId() { return renderer_program_id; };

        private:
            unsigned int CompileShader(unsigned int shaderType, const char *source);

        private:
            unsigned int renderer_program_id;
            std::unordered_map<std::string, GLint> varLocations;
        };
    }
} // namespace baka


#endif