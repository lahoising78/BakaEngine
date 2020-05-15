#include "baka_graphics.h"
#include "baka_logger.h"

namespace baka
{
    typedef struct
    {
        SDL_Window *window;
        bool initialized;
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

        graphics_manager.window = SDL_CreateWindow(
            windowName,
            0, 0,
            width, height,
            windowFlags
        );
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
}