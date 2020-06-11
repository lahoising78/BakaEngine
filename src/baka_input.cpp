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

        memset(this->input_events.mouse_button_state, 0, sizeof(uint8_t) * BAKA_MOUSE_BUTTON_NUM * 2);
        this->input_events.mouse_button_curr_side = this->input_events.mouse_button_state;
        this->input_events.mouse_button_prev_side = this->input_events.mouse_button_state + BAKA_MOUSE_BUTTON_NUM;
        SDL_StartTextInput();
    }

    void Input::Update()
    {
        // memcpy(this->input_events.prev_keyboard_events, this->input_events.keyboard_events, sizeof(uint8_t) * this->input_events.num_keys);
        
        memcpy( this->input_events.keyboard_prev_side, 
                this->input_events.keyboard_curr_side, 
                sizeof(uint8_t) * BAKA_KEYCODES_NUM);
        memcpy( this->input_events.mouse_button_prev_side, 
                this->input_events.mouse_button_curr_side,
                sizeof(uint8_t) * BAKA_MOUSE_BUTTON_NUM);
        this->input_events.quit_event = {};
        this->input_events.text_event = {};

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
            case SDL_MOUSEBUTTONUP:
                this->input_events.mouse_button_curr_side[ e.button.button ] = e.button.state;
                break;
            
            default:
                break;
            }
        }

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
        return this->input_events.mouse_button_curr_side[mouseButton];
    }

    bool Input::MouseButtonJustPressed(BakaMouseButton mouseButton)
    {
        BAKA_ASSERT(mouseButton < BAKA_MOUSE_BUTTON_NUM);
        return  this->input_events.mouse_button_curr_side[ mouseButton ] &&
                !this->input_events.mouse_button_prev_side[ mouseButton ];
    }

    bool Input::MouseButtonJustReleased(BakaMouseButton mouseButton)
    {
        BAKA_ASSERT(mouseButton < BAKA_MOUSE_BUTTON_NUM);
        return  !this->input_events.mouse_button_curr_side[ mouseButton ] &&
                this->input_events.mouse_button_prev_side[ mouseButton ];
    }

    void Input::Close()
    {
        // if(this->input_events.prev_keyboard_events)
        //     delete this->input_events.prev_keyboard_events;
        SDL_StopTextInput();
    }
}