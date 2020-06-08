#ifndef _BAKA_GRAPHICS_H_
#define _BAKA_GRAPHICS_H_

#include <SDL.h>

namespace baka{
    
    class BakaApplication;
    struct baka_app_config_s;

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
        static bool Init(struct baka_app_config_s);
        static bool IsInit();
        static void Render();
        static void Close();

        static SDL_Window *GetWindow();
        static int GetWindowWidth();
        // static void SetWindowWidth(int);
        static int GetWindowHeight();
        // static void SetWindowHeight(int);
        static const char * const GetWindowName();
        // static void SetWindowName(const char *);

    private:
        static void Setup();
    };
}

#endif