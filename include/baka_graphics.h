#ifndef _BAKA_GRAPHICS_H_
#define _BAKA_GRAPHICS_H_

#include <SDL.h>
// #include <SDL2/SDL.h>

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
        static bool Init( const char *windowName, int width, int height, uint32_t apiFlags );
        static bool IsInit();

        static SDL_Window *GetWindow();
        static int GetWidth();
        static int GetHeight();

    private:
        static void Setup( const char *windowName, int width, int height, uint32_t apiFlags );
        static void Close();
    };
}

#endif