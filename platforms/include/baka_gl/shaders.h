#ifndef _BAKA_GL_SHADERS_H_
#define _BAKA_GL_SHADERS_H_

namespace baka
{
    namespace gl
    {
        class Shader
        {
        public:
            unsigned int Create(const char *vertSource, const char *fragSource);
            void Destroy();
            void Bind();

            unsigned int GetRendererId() { return renderer_program_id; };

        private:
            unsigned int CompileShader(unsigned int shaderType, const char *source);

        private:
            unsigned int renderer_program_id;
        };
    }
} // namespace baka


#endif