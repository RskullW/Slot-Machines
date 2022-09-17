#pragma once
#include <SDL2/SDL.h>
#include <iostream>

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer
{
public:
    static Timer* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Timer();   }
    float GetDeltaTime() const { return _deltaTime; }
    
    void Start();
    bool GetStart();
    void Tick();

private:
    Timer();
    static Timer* _instance;

    int _timeNow;
    bool m_isStart;

    float _deltaTime, _lastTime;
};