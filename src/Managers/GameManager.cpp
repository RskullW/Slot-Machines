#include <iostream>
#include <utility>
#include "GameManager.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../Controls/Timer.h"
#include "../Controls/Input.h"
#include "TextureManager.h"
#include "../Objects/Background.h"
#include "SoundsManager.h"

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
    SoundsManager::GetInstance()->ParseSounds("../Assets/Parse/sounds.sml");

    CreateCursor("cursor");
    
    CreateObjects();
    CreateButtons();
    StartMusic("MainTheme");
}

void GameManager::StartSound(std::string soundID) {
    SoundsManager::GetInstance()->PlayEffect(std::move(soundID));
}

void GameManager::StartMusic(std::string musicID) {
    SoundsManager::GetInstance()->PlayMusic(musicID);
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

    DestroyObjects();
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

    for (auto* slot: _slots) {
        slot->Draw(_renderer);
    }
    
    _buttons["start"]->Draw(_renderer);
    _buttons["start"]->Update(*_cursor);
    
    _cursor->Draw(_renderer);
}

void GameManager::Tick() {
    Timer::GetInstance()->Tick();
}

void GameManager::CreateButtons() {
    _buttons["start"] = new Button("buttons", 76, 137, 76, 137, 0, 0, 687, 200);
}

void GameManager::CreateSlot() {
    // sourceH - высота спрайта, sourceW - ширина спрайта, destH - увеличение спрайта от 0 до destH в высоту, 
    // destW - увеличение спрайта от 0 до destW в ширину, sourceY - смещение картинки в листе спрайтов на Y,
    // sourceX - смещение картинки в листе спрайтов на X, destX - смещение спрайта по оси X на экране, 
    // destY - смещение спрайта по оси Y на экране
    _slots.push_back(new Slot("items", 191, 186, 191, 186, 0, 0, 30, 150));
    _slots.push_back(new Slot("items", 191, 186, 191, 186, 0, 191, 256, 150));
    _slots.push_back(new Slot("items", 191, 186, 191, 160, 0, 382, 475, 150));

}

void GameManager::CreateObjects() {
    
    _objects.push_back(new Background("background", 480, 853,480, 853));
    CreateSlot();
}

void GameManager::DestroyObjects() {
    for (auto* object: _objects) {
        object->Clean();
    }
    
    for (auto* slot: _slots) {
        slot->Clean();
    }
    
    _buttons["start"]->Clean();
}

void GameManager::SetConditionButtons() {
    if (_buttons["start"]->GetSelected() && !_buttons["start"]->GetActive()) {
        auto sourceX = _buttons["start"]->GetSource().x;
        _buttons["start"]->SetActive(true);
        _buttons["start"]->SetSourceX(sourceX*2);
    }
}