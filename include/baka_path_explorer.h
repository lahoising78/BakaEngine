#ifndef _BAKA_PATH_EXPLORER_H_
#define _BAKA_PATH_EXPLORER_H_

namespace baka
{

class PathExplorer
{
public:
    char *ReadFile(const char *filepath, size_t *pFileLength);
    
    void GetExecutableDirectory(char *dst);
    void GetWorkspaceDirectory(char *dst);
    void GetEngineDirectory(char *dst);

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