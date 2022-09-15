#include <iostream>
#include "GameManager.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

GameManager* GameManager::_sInstance = nullptr; 

void GameManager::Display(std::string message) {
    SDL_Log(message.c_str());
}

void GameManager::Initialize(const char* title, int xpos, int ypos, int w, int h, bool fullscreen) {
    int flags = (fullscreen)?SDL_WINDOW_FULLSCREEN:0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0 && TTF_Init() != 0)
    {
        SDL_Log("Init has failed: %s", SDL_GetError());
        _isRunning = false;
        return;
    }

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, w, h, flags);

    if (m_pWindow == nullptr)
    {
        SDL_Log("Init window has failed: %s", SDL_GetError());
        _isRunning = false;
        return;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_pRenderer == nullptr)
    {
        SDL_Log("Init renderer from window has failed: %s", SDL_GetError());
        _isRunning = false;
        return;
    }
}

bool GameManager::GetRunning() {
    return _isRunning;
}