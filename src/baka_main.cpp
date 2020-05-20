#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include <SDL.h>
//#include <SDL2/SDL.h>
#include "baka_logger.h"

BakaApplication *prog = NULL;
void CloseApplication();

int main(int argc, char *argv[])
{
    prog = new BakaApplication();
    if (!prog) return 0;
    bool running = false;
    bakalog("--==== Start of application ====--");
    
    prog->Main(argc, argv);
    if(prog->vk_graphics) prog->vk_graphics->Init();
    atexit(CloseApplication);
    
    running = baka::Graphics::IsInit();

    bakalog("--==== Update of application ====--");
    while(running)
    {
        baka::Input::Update();

        if( baka::Input::QuitRequested() || baka::Input::KeyPressed(SDL_SCANCODE_ESCAPE) )
        {
            running = false;
        }

        prog->Update(0.0f);
    }

    bakalog("--==== End of application ====--");
    return 0;
}

void CloseApplication()
{
    if(prog) delete prog;
}