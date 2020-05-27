#ifndef _BAKA_GL_UTILS_H_
#define _BAKA_GL_UTILS_H_

#define GLCALL(fx)  fx;\
                    baka::gl::Utils::ReadErrors(__FILE__, __LINE__)

namespace baka
{
namespace gl
{

class Utils
{
public:
    static void ReadErrors(const char *filename, unsigned int line);
};

} // namespace gl
} // namespace baka


#endif