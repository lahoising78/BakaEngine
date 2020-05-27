#include <GL/glew.h>

#include "baka_logger.h"
#include "baka_gl/utils.h"

namespace baka
{
namespace gl
{
    void Utils::ReadErrors(const char *filename, unsigned int line)
    {
        int err;
        while( err = glGetError() )
        {
            bakaerr("gl error at %s(%u): %s", filename, line, glewGetErrorString(err));
        }
    }
} // namespace gl
} // namespace baka
