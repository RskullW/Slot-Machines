#pragma once
#include <string>
#include "SDL2/SDL.h"

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
    
    bool GetRunning() const; 
    void SetRunning(bool running);
private:
    GameManager() {}
    
    static GameManager* _instance;
    bool _isRunning = true;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};