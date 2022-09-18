#include <iostream>
#include <SDL2/SDL_log.h>
#include "SoundsManager.h"
#include "../XmlParser/tinyxml.h"

SoundsManager* SoundsManager::_instance = nullptr;

SoundsManager::SoundsManager() {
    Mix_AllocateChannels(5);
    if (Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 4, CHUNK_SIZE) < 0)
    {
        std::cerr << Mix_GetError() << "\n";
    }
}

void SoundsManager::PlayMusic(std::string id) {
    if (Mix_PlayMusic(_musicMap[id], -1) == -1)
    {
        std::cerr << Mix_GetError() << ": " << id << '\n';
    }
}

void SoundsManager::StopMusic()
{
    Mix_HaltMusic();
}

void SoundsManager::LoadMusic(std::string id, std::string source) {
    Mix_Music* music = Mix_LoadMUS(source.c_str());

    if (music!= nullptr){
        _musicMap[id] = music;
    }

    else
    {
        std::cerr << Mix_GetError() << ": " << source << '\n';
    }
}

void SoundsManager::PlayEffect(std::string id, int channel, int loops) {
    if (Mix_PlayChannel(channel, _effectMap[id], loops) == -1){
        std::cerr << Mix_GetError() << ": " << id << '\n';
    }
}

void SoundsManager::StopEffect(int channel)
{
    Mix_HaltChannel(channel);
}

void SoundsManager::LoadEffect(std::string id, std::string source, int channel) {
    Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
    if (effect != nullptr)
    {
        _effectMap[id] = effect;
    }

    else
    {
        std::cerr << Mix_GetError() << ": " << source << '\n';
    }
}

void SoundsManager::Clean() {
    for (MusikMap::iterator it = _musicMap.begin(); it!=_musicMap.end(); ++it)
    {
        Mix_FreeMusic(it->second);
    }

    for (EffectMap::iterator it = _effectMap.begin(); it!=_effectMap.end(); ++it)
    {
        Mix_FreeChunk(it->second);
    }

    _musicMap.clear();
    _effectMap.clear();
}

bool SoundsManager::ParseSounds(std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error()) {
        SDL_Log("Error load music");
        return false;
    }

    TiXmlElement *root = xml.RootElement();

    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("sound")) {
            LoadEffect(e->Attribute("id"), e->Attribute("source"));
            continue;
        }

        if (e->Value() == std::string("music")) {
            LoadMusic(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
    }
    return true;
}