#include <cstdlib>
#include <cstring>

#include <SDL.h>

#include "baka_input.h"
#include "baka_logger.h"

namespace baka
{
    void Input::Init(InputConfig input_config)
    {
        memset(this->input_events.keyboard_state, 0, sizeof(uint8_t) * BAKA_KEYCODES_NUM * 2);
        this->input_events.keyboard_curr_side = this->input_events.keyboard_state;
        this->input_events.keyboard_prev_side = this->input_events.keyboard_state + BAKA_KEYCODES_NUM;

        this->input_events.mouse_buttons = ButtonState();
        SDL_StartTextInput();

        this->input_events.game_controller_num = (uint32_t)SDL_NumJoysticks();
        this->input_events.game_controllers = (GameController*)malloc(sizeof(GameController) * this->input_events.game_controller_num);
        if(this->input_events.game_controllers)
        {
            for(uint32_t i = 0; i < this->input_events.game_controller_num; i++)
            {
                GameController *control = &this->input_events.game_controllers[i];
                *control = GameController();
                control->Open(i);
            }
        }
    }

    void Input::Update()
    {
        memcpy( this->input_events.keyboard_prev_side, 
                this->input_events.keyboard_curr_side, 
                sizeof(uint8_t) * BAKA_KEYCODES_NUM);
        this->input_events.quit_event = {};
        this->input_events.text_event = {};
        this->input_events.mouse_buttons.NextState();

        SDL_Event e = {};

        while( SDL_PollEvent(&e) )
        {
            switch (e.type)
            {
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                this->input_events.keyboard_curr_side[ e.key.keysym.scancode ] = e.key.state;
                break;

            case SDL_QUIT:
                this->input_events.quit_event = e.quit;
                break;

            case SDL_TEXTINPUT:
                this->input_events.text_event = e.text;
                break;

            case SDL_MOUSEBUTTONDOWN:
                this->input_events.mouse_buttons.TurnBitsOn(MouseButtonBit(e.button.button));
                break;
                
            case SDL_MOUSEBUTTONUP:
                this->input_events.mouse_buttons.TurnBitsOff(MouseButtonBit(e.button.button));
                break;
            
            default:
                break;
            }
        }

        this->input_events.mouse_buttons.DetectButtonUpDownEvents();
    }

    bool Input::IsKeyPressed(BakaKeycode key)
    {
        BAKA_ASSERT(key < BAKA_KEYCODES_NUM);
        return input_events.keyboard_curr_side[key];
    }

    bool Input::KeyJustPressed(BakaKeycode key)
    {
        BAKA_ASSERT(key < BAKA_KEYCODES_NUM);
        return  input_events.keyboard_curr_side[key] &&
                !input_events.keyboard_prev_side[key];
    }

    bool Input::KeyJustReleased(BakaKeycode key)
    {
        BAKA_ASSERT(key < BAKA_KEYCODES_NUM);
        return  !input_events.keyboard_curr_side[key] &&
                input_events.keyboard_prev_side[key];
    }

    bool Input::AnyKey()
    {
        return this->input_events.text_event.type;
    }

    bool Input::QuitRequested()
    {
        return input_events.quit_event.type;
    }

    bool Input::IsMouseButtonPressed(BakaMouseButton mouseButton)
    {
        BAKA_ASSERT(mouseButton < BAKA_MOUSE_BUTTON_NUM);
        return this->input_events.mouse_buttons.current_button_states & (1 << mouseButton);
    }

    bool Input::MouseButtonJustPressed(BakaMouseButton mouseButton)
    {
        BAKA_ASSERT(mouseButton < BAKA_MOUSE_BUTTON_NUM);
        return this->input_events.mouse_buttons.button_downs & (1 << mouseButton);
    }

    bool Input::MouseButtonJustReleased(BakaMouseButton mouseButton)
    {
        BAKA_ASSERT(mouseButton < BAKA_MOUSE_BUTTON_NUM);
        return this->input_events.mouse_buttons.button_ups & (1 << mouseButton);
    }

    void Input::Close()
    {
        SDL_StopTextInput();

        if(this->input_events.game_controllers)
        {

            for(uint32_t i = 0; i < this->input_events.game_controller_num; i++)
            {
                this->input_events.game_controllers[i].Close();
            }

            free(this->input_events.game_controllers);
            this->input_events.game_controllers = nullptr;
            this->input_events.game_controller_num = 0;
        }
    }
}