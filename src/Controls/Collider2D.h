#pragma once

#include <SDL2/SDL.h>

class Collider2D
{
public:
    inline SDL_Rect Get() { return _box; }
    inline void SetBuff(int x, int y, int w, int h) { _buff = { x,y,w,h }; }
    void Set(int x, int y, int w, int h)
    {
        _box = { x - _buff.x, y - _buff.y, w - _buff.w, h - _buff.h };
    }
private:
    SDL_Rect _box;
    SDL_Rect _buff;
};
