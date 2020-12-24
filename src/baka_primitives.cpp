#include <cstring>

#include <baka_logger.h>
#include <baka_primitives.h>

namespace baka
{
    void PrimitiveAsString(Primitive primitive, char *buffer)
    {
        BAKA_ASSERT(buffer);

        switch (primitive)
        {
        case Primitive::CUBE:
            strcpy(buffer, "default-cube");
            break;

        case Primitive::SPHERE:
            strcpy(buffer, "default-sphere");
            break;

        case Primitive::PLANE:
            strcpy(buffer, "default-plane");
            break;

        case Primitive::CONE:
            strcpy(buffer, "default-cone");
            break;

        case Primitive::CYLINDER:
            strcpy(buffer, "default-cylinder");
            break;
        
        default:
            strcpy(buffer, "");
            break;
        }
    }
} // namespace baka