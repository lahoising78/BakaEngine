#include <cstring>
#include <cstdio>

#include <baka_logger.h>
#include <baka_path_explorer.h>

namespace baka
{
    
char *PathExplorer::ReadFile(const char *filepath, size_t *pFileLength)
{
    FILE *file = fopen(filepath, "r");
    if(!file)
    {
        bakawarn("unable to open file %s", filepath);
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    size_t fileLength = ftell(file);
    
    if(!fileLength)
    {
        bakalog("the specified file is empty: %s", filepath);
        fclose(file);
        return nullptr;
    }

    char *content = (char*)calloc( fileLength, sizeof(char) );
    if(!content)
    {
        bakalog("unable to allocate enough space for file content");
        fclose(file);
        return nullptr;
    }

    rewind(file);

    fread(content, fileLength, 1, file);
    if(pFileLength) *pFileLength = fileLength;

    fclose(file);
    return content;
}
    
void PathExplorer::GetExecutableDirectory(char *dst)
{
    strcpy(dst, BAKA_EXECUTABLE_PATH);
    bakalog("current directory: %s", dst);
}

void PathExplorer::GetWorkspaceDirectory(char *dst)
{
    strcpy(dst, BAKA_WORKSPACE_PATH);
    bakalog("workspace directory: %s", dst);
}

void PathExplorer::GetEngineDirectory(char *dst)
{
    strcpy(dst, BAKA_ENGINE_PATH);
    bakalog("engine directory: %s", dst);
}


} // namespace baka