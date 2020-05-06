#ifndef _BAKA_INPUT_H_
#define _BAKA_INPUT_H_

#include <SDL2/SDL.h>
#include "singleton_defines.h"

#define BAKA_NUM_KEYS SDL_NUM_SCANCODES

namespace baka
{
    class Input
    {
    SINGLETON_CLASS_PROPERTIES(Input)

    public:
        void Init();
        void Update();

        bool KeyPressed(int key);
        const char *AnyKey();
        bool QuitRequested();

    private:
        SDL_KeyboardEvent keyboard[ BAKA_NUM_KEYS ];
        SDL_QuitEvent quitEvent;
        SDL_TextInputEvent lastKey;
    };
}

#endif