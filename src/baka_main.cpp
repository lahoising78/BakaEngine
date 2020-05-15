#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include "SDL.h"
#include "baka_logger.h"

int main(int argc, char *argv[])
{
    bool running = false;
    bakalog("--==== Start of application ====--");

    BakaMain(argc, argv);
    running = baka::Graphics::IsInit();

    bakalog("--==== Update of application ====--");
    while(running)
    {
        baka::Input::Update();

        if( baka::Input::QuitRequested() || baka::Input::KeyPressed(SDL_SCANCODE_ESCAPE) )
        {
            running = false;
        }

        BakaUpdate(0.0f);
    }

    bakalog("--==== End of application ====--");

    return 0;
}