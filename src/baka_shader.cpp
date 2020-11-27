#include <baka_graphics.h>
#include <baka_shader.h>
#include <baka_gl/shaders.h>

namespace baka
{
    Shader *Shader::Create(const char *vertSrc, const char *fragSrc)
    {
        static Graphics &graphics = Graphics::Get();
        switch (graphics.GetEnabledAPI())
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL: return new gl::Shader(vertSrc, fragSrc);
        default: return nullptr;
        }
    }
} // namespace baka
