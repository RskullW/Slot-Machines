#pragma once
#include <SDL2/SDL.h>
#include <string>

class Animation
{
public:
    Animation(bool repeat = true) : _repeat(repeat) { _ended = false; };

    virtual void Update(float dt) = 0;
    inline bool GetEnded() { return _ended; }
protected:
    bool _repeat;
    bool _ended;
    int _curFrame;
};
