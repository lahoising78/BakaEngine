#include "baka_graphics.h"
#include "baka_logger.h"
#include "baka_gl/gl.h"
#include "baka_application.h"
#include "Baka.h"

namespace baka
{
    typedef struct
    {
        SDL_Window *window;
        char windowName[BAKA_WINDOW_NAME_MAX_LENGTH];
        int windowWidth, windowHeight;
        uint32_t apiFlags;
        bool initialized;
    } BakaGraphics;

    static BakaGraphics graphics_manager = {0};

    bool Graphics::Init(BakaApplicationConfig config)
    {
        strcpy(graphics_manager.windowName, config.initialWindowName);
        graphics_manager.windowWidth = config.initialWindowWidth;
        graphics_manager.windowHeight = config.initialWindowHeight;

        if(SDL_Init( SDL_INIT_EVERYTHING ) != 0)
        {
            bakaerr("Failed to initialize SDL");
            return false;
        }

        Graphics::Setup();

        bakalog("baka graphics initialized");
        graphics_manager.initialized = true;
        return true;
    }

    void Graphics::Setup()
    {
        uint32_t windowFlags = 0;
        const char * const windowName = graphics_manager.windowName;
        const int width = graphics_manager.windowWidth;
        const int height = graphics_manager.windowHeight;
        
        // if( graphics_manager.application->vk_graphics )
        // {
        //     windowFlags |= SDL_WINDOW_VULKAN;
        // }

        // if( graphics_manager.application->gl_graphics )
        // {
        //     windowFlags |= SDL_WINDOW_OPENGL;

        //     /* set open gl version */
        //     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        //     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        //     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        //     /* enable double buffering with 24bit depth buffer */
        //     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        //     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        // }

        graphics_manager.window = SDL_CreateWindow(
            windowName,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height,
            windowFlags
        );

        // if(graphics_manager.application->gl_graphics)
        // {
        //     graphics_manager.application->gl_graphics->Init();
        // }

        // if(graphics_manager.application->vk_graphics)
        // {
        //     graphics_manager.application->vk_graphics->Init();
        // }
    }

    void Graphics::Close()
    {
        bakalog("closing baka graphics");
        if(graphics_manager.window)
        {
            SDL_DestroyWindow( graphics_manager.window );
        }

        SDL_Quit();
    }

    void Graphics::Render()
    {
        // if(graphics_manager.application->gl_graphics)
        // {
        //     graphics_manager.application->gl_graphics->Render();
        // }
    }

    bool Graphics::IsInit()
    {
        return graphics_manager.initialized;
    }

    SDL_Window *Graphics::GetWindow()
    {
        return graphics_manager.window;
    }

    int Graphics::GetWindowWidth()
    {
        return graphics_manager.windowWidth;
    }

    // void Graphics::SetWindowWidth(int w)
    // {
    //     graphics_manager.windowWidth = w;
    // }

    int Graphics::GetWindowHeight()
    {
        return graphics_manager.windowHeight;
    }

    // void Graphics::SetWindowHeight(int h)
    // {
    //     graphics_manager.windowHeight = h;
    // }

    const char * const Graphics::GetWindowName()
    {
        return graphics_manager.windowName;
    }

    // void Graphics::SetWindowName(const char *name)
    // {
    //     snprintf(graphics_manager.windowName, sizeof(char) * BAKA_WINDOW_NAME_MAX_LENGTH, name);
    // }

}