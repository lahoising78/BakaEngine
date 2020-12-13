#ifndef _BAKA_PATH_EXPLORER_H_
#define _BAKA_PATH_EXPLORER_H_

namespace baka
{

enum ResourceType
{
    DEFAULT = 0,        /** resource path is absolute or relative to executable */
    ASSET,              /** resource in assets folder - resource not loaded in script */
    RESOURCE            /** resource in resource folder - resource loaded in script  */
};

class PathExplorer
{

public:
    char *ReadFile(const char *filepath, size_t *pFileLength, ResourceType resourceType = ResourceType::ASSET);

    static PathExplorer &Get()
    {
        static PathExplorer path_explorer = PathExplorer();
        return path_explorer;
    }

private:
    PathExplorer() { }
};

} // namespace baka

#endif