#ifndef _BAKA_SHADER_H_
#define _BAKA_SHADER_H_

namespace baka
{
    class Shader
    {
    public:
        static Shader *Create(const char *vertSrc, const char *fragSrc);
        ~Shader();
        virtual void Bind() = 0;
        virtual void Destroy();
    };
} // namespace baka


#endif