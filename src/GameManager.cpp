#include <iostream>
#include "GameManager.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Timer.h"
#include "Input.h"

GameManager* GameManager::_sInstance = nullptr; 

void GameManager::Display(const std::string& message) {
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

void GameManager::Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
}

void GameManager::Renderer() {
    SDL_RenderClear(m_pRenderer);
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
    SDL_RenderPresent(m_pRenderer);
}

void GameManager::HandleEvents() {
    Input::GetInstance()->Listen();
}

void GameManager::Tick() {
    
}

void GameManager::Clean() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameManager::SetRunning(bool running) {
    _isRunning = running;
}

bool GameManager::GetRunning() const {
    return _isRunning;
}
