#include <baka_graphics.h>
#include <baka_shader.h>
#include <baka_gl/shaders.h>
#include <baka_path_explorer.h>
#include <baka_logger.h>

namespace baka
{
    Shader *Shader::Create(char *vertSrc, char *fragSrc)
    {
        static Graphics &graphics = Graphics::Get();
        Shader *shader = nullptr;

        BAKA_ASSERT(vertSrc);
        BAKA_ASSERT(fragSrc);

        std::unordered_map<std::string, UniformType> uniforms;
        Shader::GetUniforms(vertSrc, uniforms);
        Shader::GetUniforms(fragSrc, uniforms);

        switch (graphics.GetEnabledAPI())
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL: 
            shader = new gl::Shader(vertSrc, fragSrc);
            break;
        default: return nullptr;
        }

        shader->activeUniforms = uniforms;
        return shader;
    }

    Shader *Shader::Load(const char *vertPath, const char *fragPath, ResourceType resourceType)
    {
        static PathExplorer explorer = PathExplorer::Get();
        char *vertSrc = explorer.ReadFile(vertPath, nullptr, resourceType);
        char *fragSrc = explorer.ReadFile(fragPath, nullptr, resourceType);
        Shader *shader = Shader::Create(vertSrc, fragSrc);

        if(vertSrc) delete vertSrc;
        if(fragSrc) delete fragSrc;

        return shader;
    }

    void Shader::GetUniforms(char *source, std::unordered_map<std::string, UniformType> &dst)
    {
        const char *startTerm = "#uniforms";
        const char *endTerm = "#enduniforms";

        char *start = strstr(source, startTerm);
        if(!start) return;
        char *end = strstr(start, endTerm);
        if(!end) return;

        for(char *curr = start + sizeof(startTerm) + 1; curr < end; )
        {
            while(isspace(*curr)) curr++;
            char *separator = strchr(curr, ';');
            curr += sizeof("uniform");
            while(isspace(*curr)) curr++;
            
            char *wordEnd = curr;
            while(!isspace(*wordEnd)) wordEnd++;
            *wordEnd = '\0';

            if(strcmp(curr, "mat4") == 0) 
                bakalog("found mat4");
            else if (strcmp(curr, "vec4") == 0) 
                bakalog("found vec4");

            *wordEnd = ' ';
            curr = separator + 1;
        }

        memset(start, ' ', strlen(startTerm));
        memset(end, ' ', strlen(endTerm));
    }
} // namespace baka
