#include <cstdlib>
#include <cstring>
#include "baka_input.h"
#include "baka_logger.h"

namespace baka
{
    typedef struct
    {
        SDL_KeyboardEvent keyboard[ BAKA_NUM_KEYS ];
        SDL_QuitEvent quitEvent;
        SDL_TextInputEvent lastKey;
    } BakaInput;

    static BakaInput input_manager = {0};

    void Input::Init()
    {
        memset(input_manager.keyboard, 0, sizeof(SDL_KeyboardEvent) * BAKA_NUM_KEYS);
        atexit(Input::Close);
    }

    void Input::Update()
    {
        SDL_Event e = {0};
        memset(input_manager.keyboard, 0, sizeof(SDL_KeyboardEvent) * BAKA_NUM_KEYS);
        input_manager.quitEvent = {0};
        input_manager.lastKey = {0};

        while(SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                if(e.key.keysym.scancode < BAKA_NUM_KEYS)
                {
                    input_manager.keyboard[ e.key.keysym.scancode ] = e.key;
                }
                break;

            case SDL_TEXTINPUT:
                input_manager.lastKey = e.text;
                break;

            case SDL_QUIT:
                input_manager.quitEvent = e.quit;
                break;
            
            default:
                break;
            }
        }
    }

    bool Input::KeyPressed(int key)
    {
        if(key >= BAKA_NUM_KEYS) return false;
        return input_manager.keyboard[key].state == SDL_PRESSED;
    }

    const char *Input::AnyKey()
    {
        return input_manager.lastKey.text;
    }

    bool Input::QuitRequested()
    {
        return input_manager.quitEvent.type == SDL_QUIT;
    }

    void Input::Close()
    {

    }
}