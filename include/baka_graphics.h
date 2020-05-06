#ifndef _BAKA_GRAPHICS_H_
#define _BAKA_GRAPHICS_H_

#include <SDL2/SDL.h>
#include "singleton_defines.h"

namespace baka{
    class Graphics
    {
    SINGLETON_CLASS_PROPERTIES(Graphics)
    
    public:
        bool Init( const char *windowName, int width, int height );

    private:
        void Setup( const char *windowName, int width, int height );

    private:
        SDL_Window *window;
        bool initialized;
    };
}

#endif