#include <cstdlib>
#include <cstring>

#include <SDL.h>

#include "baka_input.h"
#include "baka_logger.h"

namespace baka
{
    void Input::Init(InputConfig input_config)
    {
        memset(this->input_events.keyboard_state, 0, sizeof(uint8_t) * 512);
        this->input_events.mouse_button_curr_side = this->input_events.mouse_button_state;
        this->input_events.mouse_button_prev_side = this->input_events.mouse_button_state + 8;
        SDL_StartTextInput();
    }

    void Input::Update()
    {
        // memcpy(this->input_events.prev_keyboard_events, this->input_events.keyboard_events, sizeof(uint8_t) * this->input_events.num_keys);
        
        memset(this->input_events.keyboard_events, 0, sizeof(SDL_KeyboardEvent) * 512);
        this->input_events.quit_event = {};
        this->input_events.text_event = {};
        memcpy( this->input_events.mouse_button_prev_side, 
                this->input_events.mouse_button_curr_side,
                sizeof(uint8_t) * 8);

        SDL_Event e = {};

        while( SDL_PollEvent(&e) )
        {
            switch (e.type)
            {
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                this->input_events.keyboard_events[ e.key.keysym.scancode ] = e.key;
                this->input_events.keyboard_state[ e.key.keysym.scancode ] = e.key.state;
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

    bool Input::IsKeyPressed(int key)
    {
        BAKA_ASSERT(key < 512);
        return input_events.keyboard_state[key];
    }

    bool Input::KeyJustPressed(int key)
    {
        BAKA_ASSERT(key < 512);
        return  input_events.keyboard_events[key].type == SDL_KEYDOWN &&
                input_events.keyboard_events[key].repeat == 0;
    }

    bool Input::KeyJustReleased(int key)
    {
        BAKA_ASSERT(key < 512);
        return  input_events.keyboard_events[key].type == SDL_KEYUP;
    }

    bool Input::AnyKey()
    {
        return this->input_events.text_event.type;
    }

    bool Input::QuitRequested()
    {
        return input_events.quit_event.type;
    }

    bool Input::IsMouseButtonPressed(int mouseButton)
    {
        BAKA_ASSERT(mouseButton < 8);
        return this->input_events.mouse_button_curr_side[mouseButton];
    }

    bool Input::MouseButtonJustPressed(int mouseButton)
    {
        BAKA_ASSERT(mouseButton < 8);
        return  this->input_events.mouse_button_curr_side[ mouseButton ] &&
                !this->input_events.mouse_button_prev_side[ mouseButton ];
    }

    bool Input::MouseButtonJustReleased(int mouseButton)
    {
        BAKA_ASSERT(mouseButton < 8);
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