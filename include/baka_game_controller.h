#ifndef _BAKA_GAME_CONTROLLER_H_
#define _BAKA_GAME_CONTROLLER_H_

#include <baka_button_state.h>

namespace baka
{


class GameController
{
public:
    GameController();
    ~GameController();
    void Open(int controlled_id);
    void Close();

private:
    ButtonState button_states;
    void *controller;
    
};

} // namespace baka

#endif