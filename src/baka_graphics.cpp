#include "baka_graphics.h"
#include "baka_logger.h"
#include "baka_open_gl.h"

namespace baka
{
    typedef struct
    {
        SDL_Window *window;
        bool initialized;
        int width, height;
    } BakaGraphics;

    static BakaGraphics graphics_manager = {0};

    bool Graphics::Init( const char *windowName, int width, int height, uint32_t apiFlags )
    {
        if(SDL_Init( SDL_INIT_EVERYTHING ) != 0)
        {
            bakaerr("Failed to initialize SDL");
            return false;
        }
        atexit(SDL_Quit);

        Graphics::Setup(windowName, width, height, apiFlags);

        atexit(Graphics::Close);

        bakalog("baka graphics initialized");
        graphics_manager.initialized = true;
        return true;
    }

    void Graphics::Setup( const char *windowName, int width, int height, uint32_t apiFlags  )
    {
        uint32_t windowFlags = 0;
        
        if( apiFlags & GraphicAPI::VULKAN )
        {
            windowFlags |= SDL_WINDOW_VULKAN;
        }

        if( apiFlags & GraphicAPI::OPENGL )
        {
            windowFlags |= SDL_WINDOW_OPENGL;

            /* set open gl version */
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            /* enable double buffering with 24bit depth buffer */
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        }

        graphics_manager.window = SDL_CreateWindow(
            windowName,
            0, 0,
            width, height,
            windowFlags
        );

        if(apiFlags & GraphicAPI::OPENGL)
        {
            GLGraphics::SetContext( graphics_manager.window );
        }

        graphics_manager.width = width;
        graphics_manager.height = height;
    }

    void Graphics::Close()
    {
        bakalog("closing baka graphics");
        if(graphics_manager.window)
        {
            SDL_DestroyWindow( graphics_manager.window );
        }
    }

    bool Graphics::IsInit()
    {
        return graphics_manager.initialized;
    }

    SDL_Window *Graphics::GetWindow()
    {
        return graphics_manager.window;
    }

    int Graphics::GetWidth()
    {
        return graphics_manager.width;
    }

    int Graphics::GetHeight()
    {
        return graphics_manager.height;
    }

}