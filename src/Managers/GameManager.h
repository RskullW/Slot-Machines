#pragma once
#include <string>
#include <vector>
#include "SDL2/SDL.h"
#include "../Controls/Mouse.h"
#include "../Objects/Object.h"
#include "../Objects/Slot.h"
#include "../Controls/Button.h"
#include "../Structures/PlayerStatics.h"

#define ushort unsigned short

class GameManager {
public:
    static GameManager* GetInstance() {
        return _instance = (_instance != nullptr)?_instance: new GameManager();
    }
    void Initialize(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
    static void Display(const std::string& message);
    void Update();
    static void HandleEvents();
    void Renderer();
    SDL_Renderer* GetRenderer();
    void Clean();
    void Tick();
    
    bool GetRunning() const; 
    void SetRunning(bool running);
    
    void SetConditionButtons(); 
    void ProccessGame(bool isActive = false);
    
private:
    void LoadData();
    void CreateCursor(std::string textureID);
    void CreateSlot();
    void CreateButtons();
    
    void Draw();
    void DrawCashText();
    void DrawTextWin(int money = -1);
    void DrawTextDefeat(int money = -1);
    
    void UpdateButtons();
    void CreateObjects();
    void DestroyObjects();
    static void StartSound(std::string soundID);
    static void StartMusic(std::string musicID);
    
    void PlayRound();
    void StopRound();
    void ExitGame();
    
    void ReduceMoney(int money = 10);
    void IncreaseMoney(int money = 10);
    
    int GenerateFigures(ushort minValue = 0, ushort maxValue = 1);
    ushort ProcessFigures();

private:
    GameManager() {}
    
    static GameManager* _instance;
    bool _isRunning = true;
    ushort _runningSlots;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    Mouse* _cursor;
    std::map<std::string, Object*> _objects;
    std::vector<Slot*> _slots;
    std::map<std::string, Button*> _buttons;
    PlayerStatics _playerStatics;
};