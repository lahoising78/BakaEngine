#include "baka_graphics.h"
#include "baka_logger.h"
#include "baka_gl/gl.h"
#include "baka_application.h"
#include "Baka.h"

namespace baka
{
    static GLGraphics *gl_graphics = nullptr;

    bool Graphics::Init(WindowConfig config)
    {
        this->window_config = config;

        if(SDL_Init( SDL_INIT_EVERYTHING ) != 0)
        {
            bakaerr("Failed to initialize SDL");
            return false;
        }

        Graphics::Setup();

        bakalog("baka graphics initialized");
        this->initialized = true;
        return true;
    }

    void Graphics::Setup()
    {
        uint32_t windowFlags = 0;
        const char * const windowName = this->window_config.name;
        const int width = this->window_config.width;
        const int height = this->window_config.height;
        
        switch (this->window_config.graphics_api)
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL:
            windowFlags |= SDL_WINDOW_OPENGL;

            /* set open gl version */
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            /* enable double buffering with 24bit depth buffer */
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            break;
        
        default:
            break;
        }

        this->window = SDL_CreateWindow(
            windowName,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height,
            windowFlags
        );

        switch (this->window_config.graphics_api)
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL:
            gl_graphics = &GLGraphics::Get();
            gl_graphics->Init();
            break;
        
        default:
            break;
        }
    }

    void Graphics::Close()
    {
        bakalog("closing baka graphics");
        if(this->window)
        {
            SDL_DestroyWindow( this->window );
        }

        SDL_Quit();
    }

    void Graphics::Render()
    {
        if(gl_graphics)
        {
            gl_graphics->Render();
        }
    }

    bool Graphics::IsInit()
    {
        return this->initialized;
    }

    SDL_Window *Graphics::GetWindow()
    {
        return this->window;
    }

    int Graphics::GetWindowWidth()
    {
        return this->window_config.width;
    }

    // void Graphics::SetWindowWidth(int w)
    // {
    //     this->window_config.width = w;
    // }

    int Graphics::GetWindowHeight()
    {
        return this->window_config.height;
    }

    // void Graphics::SetWindowHeight(int h)
    // {
    //     this->window_config.height = h;
    // }

    const char * const Graphics::GetWindowName()
    {
        return this->window_config.name;
    }

    // void Graphics::SetWindowName(const char *name)
    // {
    //     snprintf(this->windowName, sizeof(char) * BAKA_WINDOW_NAME_MAX_LENGTH, name);
    // }

}