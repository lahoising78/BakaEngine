#include <cstring>
#include <cstdio>
#ifdef WIN32
#include <string>
#include <algorithm>
#endif

#include <baka_logger.h>
#include <baka_path_explorer.h>

#define PATH_BUFFER_SIZE 256

namespace baka
{
char *PathExplorer::ReadFile(const char *filepath, size_t *pFileLength, ResourceType resourceType)
{
    FILE *file = nullptr;
    char path[ PATH_BUFFER_SIZE ];
    const char *pathFormat = "%s/%s";
    
    switch (resourceType)
    {
    case ResourceType::ASSET:
        snprintf(path, PATH_BUFFER_SIZE, pathFormat, BAKA_ASSETS_DIR, filepath);
        break;
    default:
        strncpy(path, filepath, PATH_BUFFER_SIZE);
        break;
    }
    
    file = fopen(path, "r");
    // fopen_s(&file, filepath, "r");
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

} // namespace baka