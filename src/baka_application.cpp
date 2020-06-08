#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include <SDL.h>
#include "baka_logger.h"
#include "baka_application.h"

namespace baka
{

baka::Graphics *graphics = nullptr;

BakaApplication::BakaApplication()
    : running(false)
{
    graphics = &Graphics::Get();
    
    app_config.window_config.width = 800;
    app_config.window_config.height = 600;
    snprintf(app_config.window_config.name, BAKA_WINDOW_NAME_MAX_LENGTH, "Baka Engine");
    app_config.window_config.api_flags = GraphicAPIBits::BAKA_GAPI_OPENGL;
}

bool BakaApplication::Init()
{
    running = false;
    bakalog("--==== Start of application ====--");
    
    graphics->Init( this->app_config.window_config );
    
    running = graphics->IsInit();

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
        graphics->Render();
    }
}

BakaApplication::~BakaApplication()
{
    bakalog("--==== Closing application ====--");
    graphics->Close();
}

} // namespace baka