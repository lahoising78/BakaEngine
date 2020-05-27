#ifndef _BAKA_GRAPHICS_H_
#define _BAKA_GRAPHICS_H_

#include <SDL.h>

class BakaApplication;

namespace baka{

    typedef enum
    {
        NONE    = 0,
        VULKAN  = 1,
        OPENGL  = 2
    } GraphicAPI;

    class Graphics
    {    
    public:
        /** 
         * @brief initialize window
         * @param width width of the window
         * @param height height of the window
         * @param apiFlags a uint containing the flag bits for GraphicsAPIs
         */
        static bool Init( const char *windowName, int width, int height, BakaApplication *application );
        static bool IsInit();
        static void Render();

        static SDL_Window *GetWindow();
        static int GetWidth();
        static int GetHeight();

    private:
        static void Setup( const char *windowName, int width, int height );
        static void Close();
    };
}

#endif