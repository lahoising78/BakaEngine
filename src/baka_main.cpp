#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include "SDL.h"
#include "baka_logger.h"

int main(int argc, char *argv[])
{
    BakaApplication *baka = new BakaApplication();
    bool running = false;
    bakalog("--==== Start of application ====--");

    baka->Main(argc, argv);
    running = baka::Graphics::IsInit();

    bakalog("--==== Update of application ====--");
    while(running)
    {
        baka::Input::Update();

        if( baka::Input::QuitRequested() || baka::Input::KeyPressed(SDL_SCANCODE_ESCAPE) )
        {
            running = false;
        }

        baka->Update(0.0f);
    }

    bakalog("--==== End of application ====--");
    delete baka;
    return 0;
}