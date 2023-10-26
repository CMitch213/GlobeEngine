#include "States.h"

bool::States::bPaused = false;

bool States::GetPausedState()
{
    return bPaused;
}

void States::SetPausedStated(bool bPaused)
{
    States::bPaused = bPaused;
}
