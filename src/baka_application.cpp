#include <ctime>
#include <chrono>
#include <cstdint>
#include <stdio.h>
#include <SDL.h>

#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include "baka_logger.h"
#include "baka_application.h"

namespace baka
{

baka::Graphics *graphics = nullptr;
baka::Input *input = nullptr;

BakaApplication::BakaApplication()
    : running(false), app_config({})
{
    graphics = &Graphics::Get();

    app_config.window_config.width = 800;
    app_config.window_config.height = 600;
    snprintf(app_config.window_config.name, BAKA_WINDOW_NAME_MAX_LENGTH, "Baka Engine");
    app_config.window_config.api_flags = GraphicAPIBits::BAKA_GAPI_OPENGL;

    input = &Input::Get();
    // app_config.input_config.num_keys = 512;
}

bool BakaApplication::Init()
{
    baka_log_init();
    
    running = false;
    bakalog("--==== Start of application ====--");
    
    graphics->Init( this->app_config.window_config );
    input->Init({});
    
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
    std::chrono::high_resolution_clock::time_point lastTimestamp = std::chrono::high_resolution_clock::now();   
    uint32_t frameCounter = 0;

    bakalog("--==== Update of application ====--");
    while(running)
    {
        input->Update();

        if( input->QuitRequested() || input->IsKeyPressed(SDL_SCANCODE_ESCAPE) )
        {
            running = false;
        }

        this->Update();
        graphics->Render();

        frameCounter++;

        auto tEnd = std::chrono::high_resolution_clock::now();
        double fpsTimer = std::chrono::duration<double, std::milli>(tEnd - lastTimestamp).count();

        if (fpsTimer > 1000.0f)
		{
			bakalog("fps: %f", (float)frameCounter * (1000.0f / fpsTimer));
			frameCounter = 0;
			lastTimestamp = tEnd;
		}
    }
}

BakaApplication::~BakaApplication()
{
    bakalog("--==== Closing application ====--");
    input->Close();
    graphics->Close();
}

} // namespace baka