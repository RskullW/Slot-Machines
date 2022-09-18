#include "src/Managers/GameManager.h"

const unsigned int SCREEN_WIDTH = 853;
const unsigned int SCREEN_HEIGHT = 480;

void WorkThread();

int WinMain (int argc, char * args []) {
    
    std::thread thread(WorkThread);
    std::cout << "Number thread: " << thread.get_id() << '\n';
    thread.join();

    return 0;
};

void WorkThread() {

    GameManager::GetInstance()->Initialize("Slot machines", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    
    while (GameManager::GetInstance()->GetRunning()) {
        GameManager::GetInstance()->HandleEvents();
        GameManager::GetInstance()->Update();
        GameManager::GetInstance()->Renderer();
        GameManager::GetInstance()->Tick();
    }
}