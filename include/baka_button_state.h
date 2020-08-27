#ifndef _BAKA_BUTTON_STATE_
#define _BAKA_BUTTON_STATE_

#include <cstdint>

namespace baka
{

/** 
 * @note this class can only hold up to 32 buttons
 */
class ButtonState
{
friend class Input;

public:
    ButtonState();
    void DetectButtonUpDownEvents();
    inline void TurnBitsOn(uint32_t bits)
    {
        this->current_button_states |= bits;
    }

    inline void TurnBitsOff(uint32_t bits)
    {
        this->current_button_states &= ~bits;
    }

protected:
    void NextState();

protected:
    uint32_t previous_button_states;
    uint32_t current_button_states;
    uint32_t button_downs;
    uint32_t button_ups;

};
    
} // namespace baka

#endif