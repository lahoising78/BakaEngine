#include <fstream>

#include "baka_utils.h"

namespace baka
{

    std::string Utils::ReadFile(const char *filepath)
    {
        std::string content;

        std::ifstream t(filepath);
        t.seekg(0, std::ios::end);
        content.resize(t.tellg());
        t.seekg(0, std::ios::beg);

        content.assign(
            std::istreambuf_iterator<char>(t),
            std::istreambuf_iterator<char>()
        );

        return content;
    }

}