#pragma once
#include <string>
#include "SDL2/SDL.h"

class GameManager {
public:
    static GameManager* GetInstance() {
        return _sInstance = (_sInstance != nullptr)?_sInstance: new GameManager();
    }
    void Initialize(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
    void Display(std::string message);
    void Update();
    void HandleEvenets();
    void Renderer();
    void Tick();
    void Clean();
    
    bool GetRunning(); 
private:
    GameManager() {
        _isInitialize = false;
    }
    
    static GameManager* _sInstance;
    bool _isRunning = true;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
};