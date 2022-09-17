#pragma once

#include <map>
#include <string>
#include "SDL2/SDL_mixer.h"

#define FREQ 44100
#define CHUNK_SIZE 2048

using MusikMap = std::map<std::string, Mix_Music*>;
using EffectMap = std::map<std::string, Mix_Chunk*>;

class SoundsManager {
public:
    void Clean();

    
    void PlayMusic(std::string id);
    void LoadMusic(std::string id, std::string source);
    void StopMusic();

    void PlayEffect(std::string id, int channel = -1, int loops = 0);
    void LoadEffect(std::string id, std::string source, int channel = -1);
    void StopEffect(int channel = -1);

    void FreeChunk(std::string id);

    bool ParseSounds(std::string source);

    inline static SoundsManager* GetInstance() {return _instance = (_instance != nullptr)?_instance:new SoundsManager();}

private:
    SoundsManager();
    MusikMap _musicMap;
    EffectMap _effectMap;

    static SoundsManager* _instance;
};