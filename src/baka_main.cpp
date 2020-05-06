#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include "SDL.h"
#include "baka_logger.h"

int main(int argc, char *argv[])
{
    baka::Graphics *baka_graph = baka::Graphics::Get();
    bool running = false;
    bakalog("--==== Start of application ====--");

    running = baka_graph->Init("Baka Engine", 1280, 720);
    baka::Input *baka_in = baka::Input::Get();
    
    BakaMain(argc, argv);

    bakalog("--==== Update of application ====--");
    while(running)
    {
        baka_in->Update();

        if( baka_in->QuitRequested() || baka_in->KeyPressed(SDL_SCANCODE_ESCAPE) )
        {
            running = false;
        }

        BakaUpdate(0.0f);
    }

    bakalog("--==== End of application ====--");

    return 0;
}