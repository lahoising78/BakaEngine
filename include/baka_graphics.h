#ifndef _BAKA_GRAPHICS_H_
#define _BAKA_GRAPHICS_H_

#include <cstdint>
#include <SDL.h>

#define BAKA_WINDOW_NAME_MAX_LENGTH 256

namespace baka{
    typedef enum
    {
        BAKA_GAPI_NONE    = 0,
        BAKA_GAPI_VULKAN  = 1,
        BAKA_GAPI_OPENGL  = 2
    } GraphicsAPI;
    
    typedef struct
    {
        int width, height;
        char name[BAKA_WINDOW_NAME_MAX_LENGTH];
        GraphicsAPI graphics_api;
    } WindowConfig;

    class Graphics
    {    
    public:
        /** 
         * @brief initialize window
         * @param width width of the window
         * @param height height of the window
         * @param apiFlags a uint containing the flag bits for GraphicsAPIs
         */
        bool Init(WindowConfig);
        bool IsInit();
        void Render();
        void Close();

        SDL_Window *GetWindow();
        int GetWindowWidth();
        // static void SetWindowWidth(int);
        int GetWindowHeight();
        // static void SetWindowHeight(int);
        const char * const GetWindowName();
        // static void SetWindowName(const char *);

        baka::GraphicsAPI GetEnabledAPI() { return this->window_config.graphics_api; }

        static Graphics &Get()
        {
            static Graphics graphics = Graphics();
            return graphics;
        }

    private:
        Graphics() : window(nullptr), window_config({}), initialized(false) {}
        void Setup();

    private:
        SDL_Window *window;
        WindowConfig window_config;
        bool initialized;
    };
}

#endif