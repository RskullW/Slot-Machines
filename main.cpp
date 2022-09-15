#include <iostream>
#include "src/GameManager.h"

GameManager* gameManager;

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
int WinMain (int argc, char * args []) {
    
    GameManager::GetInstance()->Initialize("Slot machines", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while (GameManager::GetInstance()->GetRunning()) {
        GameManager::GetInstance()->HandleEvents();
        GameManager::GetInstance()->Update();
        GameManager::GetInstance()->Renderer();
        GameManager::GetInstance()->Tick();
    }

    return 0;
};