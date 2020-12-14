#ifndef _BAKA_PRIMITIVES_H_
#define _BAKA_PRIMITIVES_H_

namespace baka
{
    
enum Primitive
{
    CUBE,
    SPHERE,
    PLANE,
    CONE,
    CYLINDER
};

void PrimitiveAsString(Primitive primitive, char *buffer);

} // namespace baka


#endif