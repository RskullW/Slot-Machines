#pragma once

#include "../Structures/PlayerStatics.h"
#include "iostream"
#include "string"

class SaveManagers {
public:
    static SaveManagers* GetInstance() {
        return _instance = (_instance != nullptr)?_instance: new SaveManagers();
    }
    
    void Initialize(std::string filePath);
    void LoadFile();
    void SaveFile(PlayerStatics playerStatics) const;
    PlayerStatics GetStats() const;
    void LoadStats(PlayerStatics playerStatics);
    
private:
    static SaveManagers* _instance;
    
    bool _isFilePath;
    std::string _filePath;
    PlayerStatics _playerStatics;
    
};