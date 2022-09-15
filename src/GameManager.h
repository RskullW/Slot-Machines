#pragma once
#include <string>
#include "SDL2/SDL.h"

class GameManager {
public:
    static GameManager* GetInstance() {
        return _sInstance = (_sInstance != nullptr)?_sInstance: new GameManager();
    }
    void Initialize(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
    static void Display(const std::string& message);
    void Update();
    static void HandleEvents();
    void Renderer();
    void Tick();
    void Clean();
    
    bool GetRunning() const; 
    void SetRunning(bool running);
private:
    GameManager() {}
    
    static GameManager* _sInstance;
    bool _isRunning = true;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
};