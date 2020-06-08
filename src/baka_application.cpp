#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include <SDL.h>
//#include <SDL2/SDL.h>
#include "baka_logger.h"
#include "baka_application.h"

namespace baka
{

BakaApplication::BakaApplication()
    : running(false)
{
    app_config = {};
    app_config.initialWindowWidth = 800;
    app_config.initialWindowHeight = 600;
    snprintf(app_config.initialWindowName, BAKA_WINDOW_NAME_MAX_LENGTH, "Baka Engine");
}

bool BakaApplication::Init()
{
    running = false;
    bakalog("--==== Start of application ====--");
    
    baka::Graphics::Init(app_config);
    
    running = baka::Graphics::IsInit();

    return running;
}

void BakaApplication::Start()
{
    this->Init();
    this->Run();
}

void BakaApplication::Run()
{
    bakalog("--==== Update of application ====--");
    while(running)
    {
        baka::Input::Update();

        if( baka::Input::QuitRequested() || baka::Input::KeyPressed(SDL_SCANCODE_ESCAPE) )
        {
            running = false;
        }

        this->Update();
        baka::Graphics::Render();
    }
}

BakaApplication::~BakaApplication()
{
    baka::Graphics::Close();
}

} // namespace baka