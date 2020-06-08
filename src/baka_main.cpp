// #include "Baka.h"
// #include "baka_graphics.h"
// #include "baka_input.h"
// #include <SDL.h>
// //#include <SDL2/SDL.h>
// #include "baka_logger.h"

// int main(int argc, char *argv[])
// {
//     bool running = false;
//     bakalog("--==== Start of application ====--");
    
//     prog = BakaApplication(argc, argv);
//     atexit(CloseApplication);

//     baka::Graphics::Init();
    
//     running = baka::Graphics::IsInit();

//     bakalog("--==== Update of application ====--");
//     while(running)
//     {
//         baka::Input::Update();

//         if( baka::Input::QuitRequested() || baka::Input::KeyPressed(SDL_SCANCODE_ESCAPE) )
//         {
//             running = false;
//         }

//         // prog->Update(0.0f);
//         baka::Graphics::Render();
//     }

//     bakalog("--==== End of application ====--");
//     return 0;
// }

// void CloseApplication()
// {
//     prog.Destroy();
//     baka::Graphics::Close();
// }