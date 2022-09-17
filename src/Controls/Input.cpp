#include "Input.h"
#include "../Managers/GameManager.h"

Input* Input::_instance = nullptr;

Input::Input()
{
    _keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
    SDL_Event mEvent;

    while (SDL_PollEvent(&mEvent))
    {

        switch (mEvent.type)
        {
            case SDL_QUIT: GameManager::GetInstance()->SetRunning(false); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
            case SDL_MOUSEBUTTONDOWN: MouseDown(); break;
            default:break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return (_keyStates[key] == 1);
}

void Input::KeyUp()
{
    _keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    _keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::MouseDown()
{
    GameManager::GetInstance()->SetConditionButtons();
}

int Input::GetAxisRey(Axis axis)
{
    switch (axis)
    {
        case HORIZONTAL:
        {
            if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT))
            {
                return -1;
            }

            if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT))
            {
                return 1;
            }
        }break;

        case VERTICAL:
        {
            if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP) || GetKeyDown(SDL_SCANCODE_SPACE))
            {
                return 1;
            }
            if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN))
            {
                return -1;
            }
        }break;

        default: return 0;
    }

    return 0;
}

bool Input::GetKey()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    return ((event.type == SDL_KEYUP) ? 1 : 0);
}

bool Input::GetMouseButton() {
    SDL_Event event;
    SDL_PollEvent(&event);
    
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        return true;
    }
    
    return false;
}