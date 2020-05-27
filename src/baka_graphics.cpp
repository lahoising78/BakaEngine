#include "baka_graphics.h"
#include "baka_logger.h"
#include "baka_open_gl.h"
#include "Baka.h"

namespace baka
{
    typedef struct
    {
        SDL_Window *window;
        bool initialized;
        int width, height;
        uint32_t apiFlags;
        BakaApplication *application;
    } BakaGraphics;

    static BakaGraphics graphics_manager = {0};

    bool Graphics::Init( const char *windowName, int width, int height, BakaApplication *application )
    {
        if(!application)
        {
            bakaerr("No application was provided. Cannot initialize graphics");
            return false;
        }

        if(SDL_Init( SDL_INIT_EVERYTHING ) != 0)
        {
            bakaerr("Failed to initialize SDL");
            return false;
        }
        atexit(SDL_Quit);

        graphics_manager.application = application;
        Graphics::Setup(windowName, width, height);

        atexit(Graphics::Close);

        bakalog("baka graphics initialized");
        graphics_manager.initialized = true;
        return true;
    }

    void Graphics::Setup( const char *windowName, int width, int height )
    {
        uint32_t windowFlags = 0;
        
        if( graphics_manager.application->vk_graphics )
        {
            windowFlags |= SDL_WINDOW_VULKAN;
        }

        if( graphics_manager.application->gl_graphics )
        {
            windowFlags |= SDL_WINDOW_OPENGL;

            /* set open gl version */
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
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

        graphics_manager.width = width;
        graphics_manager.height = height;

        if(graphics_manager.application->gl_graphics)
        {
            graphics_manager.application->gl_graphics->Init();
        }

        if(graphics_manager.application->vk_graphics)
        {
            graphics_manager.application->vk_graphics->Init();
        }
    }

    void Graphics::Close()
    {
        bakalog("closing baka graphics");
        if(graphics_manager.window)
        {
            SDL_DestroyWindow( graphics_manager.window );
        }
    }

    void Graphics::Render()
    {
        if(graphics_manager.application->gl_graphics)
        {
            graphics_manager.application->gl_graphics->Render();
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