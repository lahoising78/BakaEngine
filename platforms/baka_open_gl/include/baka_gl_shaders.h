#ifndef _BAKA_GL_SHADERS_H_
#define _BAKA_GL_SHADERS_H_

namespace baka
{
    class GLShader
    {
    public:
        unsigned int Create(const char *vertSource, const char *fragSource);
        void Destroy();
        void Bind();

    private:
        unsigned int CompileShader(unsigned int shaderType, const char *source);

    private:
        unsigned int program;
    };
} // namespace baka


#endif