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
        
        default:
            strcpy(buffer, "");
            break;
        }
    }
} // namespace baka