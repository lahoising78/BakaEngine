#ifndef _BAKA_UTILS_H_
#define _BAKA_UTILS_H_

#include <string>

namespace baka
{
    typedef struct
    {
        uint32_t count;
        void *data;
    } Array;

    class Utils
    {
    public:
        static std::string ReadFile(const char *filepath);
    };
} // namespace baka


#endif