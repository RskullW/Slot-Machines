#pragma once
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontManager {
public:
    static FontManager* GetInstance() {return _instance = (_instance !=nullptr)? _instance: new FontManager();}

    void Add(std::string path, std::string id, int size);
    void ClearID(std::string id);
    void Clear();

    TTF_Font* GetFont(std::string id);

private:
    FontManager() {};

private:

    std::map<std::string, TTF_Font*> _fontMap;
    static FontManager* _instance;

};