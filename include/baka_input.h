#ifndef _BAKA_INPUT_H_
#define _BAKA_INPUT_H_

#include <cstdint>
#include "baka_keycodes.h"
#include "baka_mousebuttons.h"
#include "baka_button_state.h"

namespace baka
{

typedef struct
{
    uint8_t             *keyboard_curr_side;
    uint8_t             *keyboard_prev_side;

    ButtonState         mouse_buttons;

    SDL_QuitEvent       quit_event;

    SDL_TextInputEvent  text_event;

    uint8_t             keyboard_state[BAKA_KEYCODES_NUM * 2];
} InputEvents;

typedef struct
{
    // int num_keys;
} InputConfig;

class Input
{

public:
    void Init(InputConfig);
    void Update();
    void Close();

    /* KEYBOARD EVENTS */
    bool IsKeyPressed(BakaKeycode key);
    bool KeyJustPressed(BakaKeycode key);
    bool KeyJustReleased(BakaKeycode key);
    bool AnyKey();

    /* QUIT EVENT */
    bool QuitRequested();

    /* MOUSE BUTTON EVENTS */
    bool IsMouseButtonPressed(BakaMouseButton mouseButton);
    bool MouseButtonJustPressed(BakaMouseButton mouseButton);
    bool MouseButtonJustReleased(BakaMouseButton mouseButton);

    static Input &Get()
    {
        static Input g_input = Input();
        return g_input;
    }

private:
    Input() {}

private:
    InputEvents input_events;
};

}

#endif