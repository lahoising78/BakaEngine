#include <baka_graphics.h>
#include <baka_shader.h>
#include <baka_gl/shaders.h>
#include <baka_path_explorer.h>
#include <baka_logger.h>

namespace baka
{
    Shader *Shader::Create(const char *vertSrc, const char *fragSrc)
    {
        static Graphics &graphics = Graphics::Get();

        BAKA_ASSERT(vertSrc);
        BAKA_ASSERT(fragSrc);

        switch (graphics.GetEnabledAPI())
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL: return new gl::Shader(vertSrc, fragSrc);
        default: return nullptr;
        }
    }

    Shader *Shader::Load(const char *vertPath, const char *fragPath, ResourceType resourceType)
    {
        static PathExplorer explorer = PathExplorer::Get();
        const char *vertSrc = explorer.ReadFile(vertPath, nullptr, resourceType);
        const char *fragSrc = explorer.ReadFile(fragPath, nullptr, resourceType);
        Shader *shader = Shader::Create(vertSrc, fragSrc);

        if(vertSrc) delete vertSrc;
        if(fragSrc) delete fragSrc;

        return shader;
    }
} // namespace baka
