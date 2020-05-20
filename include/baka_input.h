#ifndef _BAKA_INPUT_H_
#define _BAKA_INPUT_H_

#include <SDL.h>

#define BAKA_NUM_KEYS SDL_NUM_SCANCODES

namespace baka
{
    class Input
    {

    public:
        static void Init();
        static void Update();

        static bool KeyPressed(int key);
        static const char *AnyKey();
        static bool QuitRequested();

    private:
        static void Close();
    };
}

#endif