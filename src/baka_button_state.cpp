#include <baka_logger.h>
#include <baka_button_state.h>

namespace baka
{
    
ButtonState::ButtonState()
{
    previous_button_states = 0;
    current_button_states = 0;
    button_ups = 0;
    button_downs = 0;
}

void ButtonState::DetectButtonUpDownEvents()
{
    uint32_t buttonChanges = current_button_states ^ previous_button_states;
    button_downs = buttonChanges & current_button_states;
    button_ups = buttonChanges & (~current_button_states);
}

void ButtonState::NextState()
{
    previous_button_states = current_button_states;
}

} // namespace baka