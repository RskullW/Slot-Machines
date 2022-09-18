#pragma once

#include <SDL2/SDL.h>
#include "../Enums/Axis.h"

class Input
{
public:
    static Input* GetInstance()
    {
        return _instance = (_instance != nullptr) ? _instance : new Input();
    }

    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    
    bool GetKey();
    bool GetMouseButton();

    int GetAxisRey(Axis axis);

private:
    Input();
    void KeyUp();
    void KeyDown();
    void MouseDown();
    
    const Uint8* _keyStates;

    static Input* _instance;
};