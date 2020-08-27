#include <SDL.h>

#include <baka_logger.h>
#include <baka_game_controller.h>

namespace baka
{

GameController::GameController()
{
    this->button_states = ButtonState();
    this->controller = nullptr;
    bakalog("game controller contructor");
}

GameController::~GameController()
{
    this->Close();
    bakalog("game controller destructor");
}

void GameController::Open(int controlled_id)
{
    this->controller = SDL_JoystickOpen(controlled_id);
}

void GameController::Close()
{
    SDL_Joystick *joy = (SDL_Joystick*)this->controller;
    if(joy)
    {
        SDL_JoystickClose(joy);
    }
    this->controller = nullptr;
    bakalog("game controller close");
}
    
} // namespace baka