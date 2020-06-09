#ifndef _BAKA_INPUT_H_
#define _BAKA_INPUT_H_

#include <cstdint>

namespace baka
{

typedef struct
{
    uint8_t             keyboard_state[512];
    SDL_KeyboardEvent   keyboard_events[512];
    
    SDL_QuitEvent       quit_event;

    SDL_TextInputEvent  text_event;

    uint8_t             *mouse_button_curr_side;
    uint8_t             *mouse_button_prev_side;
    uint8_t             mouse_button_state[8 * 2];
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
    bool IsKeyPressed(int key);
    bool KeyJustPressed(int key);
    bool KeyJustReleased(int key);
    bool AnyKey();

    /* QUIT EVENT */
    bool QuitRequested();

    /* MOUSE BUTTON EVENTS */
    bool IsMouseButtonPressed(int mouseButton);
    bool MouseButtonJustPressed(int mouseButton);
    bool MouseButtonJustReleased(int mouseButton);

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