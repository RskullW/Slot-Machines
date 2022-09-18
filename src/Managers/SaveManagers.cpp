#include <SDL2/SDL_log.h>
#include <fstream>
#include "SaveManagers.h"

SaveManagers* SaveManagers::_instance = nullptr;

void SaveManagers::SaveFile(PlayerStatics playerStatics) const {
    if (!_isFilePath) {
        SDL_Log("The file path was not entered");
        return;
    }

    std::ofstream fileOut;          
    
    fileOut.open("../PlayerStats.txt", std::ios::trunc); 

    if (fileOut.is_open())
    {
        fileOut << playerStatics.Money;
    }

    fileOut.close();
}

void SaveManagers::LoadFile() {
    if (!_isFilePath) {
        SDL_Log("The file path was not entered");
        return;
    }

    std::ifstream fileIn("../PlayerStats.txt");


    if (fileIn.is_open())
    {
       fileIn >> _playerStatics.Money;
    }

    fileIn.close();
}

void SaveManagers::Initialize(std::string filePath) {
    _filePath = filePath;
    _isFilePath = true;
}

PlayerStatics SaveManagers::GetStats() const {
    return _playerStatics;
}

void SaveManagers::LoadStats(PlayerStatics playerStatics) {
    _playerStatics = playerStatics;
}