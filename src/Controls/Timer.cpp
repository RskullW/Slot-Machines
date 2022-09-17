#include "Timer.h"
#include "../Managers/GameManager.h"

Timer* Timer::_instance = nullptr;

Timer::Timer() {
    _timeNow = 0;
}

void Timer::Tick()
{
    _deltaTime = (SDL_GetTicks() - _lastTime) * (TARGET_FPS / 1000.0f);

    if (_deltaTime > TARGET_DELTATIME)
    {
        _deltaTime = TARGET_DELTATIME;
    }

    _lastTime = SDL_GetTicks();
}
void Timer::Start() {
    _timeNow = 0;
    m_isStart = true;
}
bool Timer::GetStart() {
    return m_isStart;
}
