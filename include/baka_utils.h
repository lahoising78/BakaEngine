#ifndef _BAKA_UTILS_H_
#define _BAKA_UTILS_H_

#include <string>

namespace baka
{
    class Utils
    {
    public:
        static std::string ReadFile(const char *filepath);
    };
} // namespace baka


#endif