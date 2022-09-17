#include <iostream>
#include "GameManager.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Timer.h"
#include "Input.h"
#include "TextureManager.h"
#include "Background.h"

GameManager* GameManager::_instance = nullptr; 

void GameManager::Display(const std::string& message) {
    SDL_Log(message.c_str());
}

void GameManager::Initialize(const char* title, int xpos, int ypos, int w, int h, bool fullscreen) {
    
    int flags = (fullscreen)?SDL_WINDOW_FULLSCREEN:0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0 && TTF_Init() != 0)
    {
        Display("Init has failed");
        _isRunning = false;
        return;
    }

    _window = SDL_CreateWindow(title, xpos, ypos, w, h, flags);

    if (_window == nullptr)
    {
        Display("Init window has failed");
        _isRunning = false;
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (_renderer== nullptr)
    {
        Display("Init renderer from window has failed");
        _isRunning = false;
        return;
    }
    
    TextureManager::GetInstance()->ParseTextures("../Assets/Parse/texture.tml");

    CreateCursor("cursor");
    
    _objects.push_back(new Background("background", 480, 1000,480, 1000));
    _objects.push_back(new Background("frame", 1000, 678,200, 200, 0, 0, 100, 100));



}

void GameManager::Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
    _cursor->Update();
}

void GameManager::Renderer() {
    SDL_RenderClear(_renderer);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    
    Draw();
    
    SDL_RenderPresent(_renderer);
    
}

void GameManager::HandleEvents() {
    Input::GetInstance()->Listen();
}

void GameManager::Clean() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);

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
SDL_Renderer* GameManager::GetRenderer() {
    return _renderer;
}

void GameManager::CreateCursor(std::string textureID) {
    _cursor = new Mouse(textureID);
}

void GameManager::Draw() {

    for (auto *object : _objects) {
        object->Draw(_renderer);
    }

    _cursor->Draw(_renderer);
}

void GameManager::Tick() {
    Timer::GetInstance()->Tick();
}