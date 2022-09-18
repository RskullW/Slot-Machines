#include <iostream>
#include <utility>
#include <algorithm>
#include "GameManager.h"
#include "TextureManager.h"
#include "SoundsManager.h"
#include "SaveManagers.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../Controls/Timer.h"
#include "../Controls/Input.h"
#include "../Objects/Background.h"

#define SIZE_WIDGHT_BUTTON 137
#define SIZE_HEIGHT_BUTTON 76
#define MONEY_WHEN_WINNING 50
#define MONEY_WHEN_DEFEAT 10

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
    LoadData();
    
    _runningSlots = 0;
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
    float dt = Timer::GetInstance()->GetDeltaTime();

    _objects["frames"]->Draw(_renderer);
    
    for (auto* slot: _slots) {
        slot->Update(dt);
        slot->Draw(_renderer);
    }

    _objects["background"]->Draw(_renderer);

    UpdateButtons();
    
    _cursor->Draw(_renderer);
}

void GameManager::Tick() {
    Timer::GetInstance()->Tick();
}

void GameManager::CreateButtons() {
    _buttons["start"] = new Button("buttons", SIZE_HEIGHT_BUTTON, SIZE_WIDGHT_BUTTON, SIZE_HEIGHT_BUTTON, SIZE_WIDGHT_BUTTON, 0, 0, 687, 175);
    _buttons["stop"] = new Button("buttons", SIZE_HEIGHT_BUTTON, SIZE_WIDGHT_BUTTON, SIZE_HEIGHT_BUTTON, SIZE_WIDGHT_BUTTON, 0, SIZE_HEIGHT_BUTTON, 687, 260);
    _buttons["exit"] = new Button("buttons", SIZE_HEIGHT_BUTTON, SIZE_WIDGHT_BUTTON, SIZE_HEIGHT_BUTTON, SIZE_WIDGHT_BUTTON, 0, SIZE_HEIGHT_BUTTON*2, 687, 360);


    auto sourceX = _buttons["start"]->GetSource().x;
    _buttons["stop"]->SetActive(true);
    _buttons["stop"]->SetSourceX(SIZE_WIDGHT_BUTTON*2);
}

void GameManager::CreateSlot() {
    // sourceH - высота спрайта, sourceW - ширина спрайта, destH - увеличение спрайта от 0 до destH в высоту, 
    // destW - увеличение спрайта от 0 до destW в ширину, sourceY - смещение картинки в листе спрайтов на Y,
    // sourceX - смещение картинки в листе спрайтов на X, destX - смещение спрайта по оси X на экране, 
    // destY - смещение спрайта по оси Y на экране

    srand(time(0));

    _slots.push_back(new Slot("items", 337, 190, 337, 190, 0, GenerateFigures(0, 9), 40, 70));
    _slots.push_back(new Slot("items", 337, 190, 337, 190, 0, GenerateFigures(0, 9), 260, 70));
    _slots.push_back(new Slot("items", 337, 190, 337, 150, 0, GenerateFigures(0, 9), 480, 70));

}

void GameManager::CreateObjects() {
    _objects["frames"] = new Background("frame", 349, 631,349, 631, 0, 0, 19, 65);
    _objects["background"] = new Background("background", 480, 853,480, 853);
    CreateSlot();

}

void GameManager::DestroyObjects() {

    for (auto & object : _objects) {
        object.second->Draw(_renderer);
    }
    
    for (auto* slot: _slots) {
        slot->Clean();
    }
    
    _buttons["start"]->Clean();
    _buttons["stop"]->Clean();

    SaveManagers::GetInstance()->SaveFile(_playerStatics);
}

void GameManager::SetConditionButtons() {

    if (_buttons["stop"]->GetSelected() && !_buttons["stop"]->GetActive()) {
        StopRound();
        _buttons["stop"]->SetActive(true);
        _buttons["stop"]->SetSourceX(SIZE_WIDGHT_BUTTON * 2);
    }
    
    if (_buttons["start"]->GetSelected() && !_buttons["start"]->GetActive()) {
        auto sourceX = _buttons["start"]->GetSource().x;
        PlayRound();
        _buttons["start"]->SetActive(true);
        _buttons["start"]->SetSourceX(sourceX * 2);
    }

    if (_buttons["exit"]->GetSelected() && !_buttons["exit"]->GetActive()) {
        auto sourceX = _buttons["exit"]->GetSource().x;
        ExitGame();
        _buttons["exit"]->SetActive(true);
        _buttons["exit"]->SetSourceX(sourceX * 2);
    }
}

void GameManager::PlayRound() {
    std::cout << "\n" << _playerStatics.Money;
    if (!_buttons["start"]->GetActive()) {
        StartSound("RotationSlots");
        SoundsManager::GetInstance()->StopMusic();
        
        for (auto* slot: _slots) {
            slot->StartRotate();
        }
        
        _runningSlots = 3;

        _buttons["stop"]->SetActive(false);
        _buttons["stop"]->SetSourceX(0);

        ReduceMoney(MONEY_WHEN_DEFEAT);
    }
}

void GameManager::StopRound() {
    for (Slot* slot: _slots) {
        slot->StopRotate();
    }
}

void GameManager::ProccessGame(bool isActive) {
    auto *buttonStart = _buttons["start"];
    auto *buttonStop = _buttons["stop"];

    if (_buttons["start"]->GetActive()) {
        _runningSlots -= 1;

        if (_runningSlots == 0) {

            SoundsManager::GetInstance()->StopEffect();

            if (ProcessFigures()) {
                StartSound("WinningSound");
                IncreaseMoney(MONEY_WHEN_WINNING);
            } else {
                StartSound("FailedSound");
            }

            buttonStart->SetActive(isActive);
            buttonStop->SetActive(true);
            buttonStop->SetSourceX(SIZE_WIDGHT_BUTTON*2);
            
            SoundsManager::GetInstance()->PlayMusic("MainTheme");

        }
    }
}

int GameManager::GenerateFigures(ushort minValue, ushort maxValue) {
    
    int randomIndexFigure = (int)(minValue + rand() % (maxValue - minValue));
    std::cout << "Index figure: " << randomIndexFigure << "\n";
    return randomIndexFigure*337;
}

bool GameManager::ProcessFigures() {
    
    
    for (ushort i = 0; i < (ushort)_slots.size()-1; ++i) {
        std::cout << "\nindex " << i << " = " << _slots[i]->GetIndexFigure();
        std::cout << "\nindex " << i+1 << " = " << _slots[i+1]->GetIndexFigure();
        if (_slots[i]->GetIndexFigure()!=_slots[i+1]->GetIndexFigure()) {
            return false;
        }
    }
    
    return true;
}

void GameManager::UpdateButtons() {

    for (auto & button : _buttons) {
        button.second->Draw(_renderer);
        button.second->Update(*_cursor);
    }
}

void GameManager::ExitGame() {
    _isRunning = false;
    SaveManagers::GetInstance()->SaveFile(_playerStatics);
}

void GameManager::LoadData() {
    SaveManagers::GetInstance()->Initialize("../PlayerStats.txt");
    SaveManagers::GetInstance()->LoadFile();

    _playerStatics = SaveManagers::GetInstance()->GetStats();
    
    if (_playerStatics.Money < 10) {
        _playerStatics.Money = 100;
    }
    
    std::cout << _playerStatics.Money;
}

void GameManager::IncreaseMoney(int money) {
    _playerStatics.Money+=money;
    SaveManagers::GetInstance()->SaveFile(_playerStatics);

}

void GameManager::ReduceMoney(int money) {
    _playerStatics.Money-=money;
    SaveManagers::GetInstance()->SaveFile(_playerStatics);

}