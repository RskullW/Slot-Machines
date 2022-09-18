#pragma once
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define DURATION_ANIMATION 70.f
#define SIZE_TEXT_FOR_END_ROTATE 70

class FontManager {
public:
    static FontManager* GetInstance() {return _instance = (_instance !=nullptr)? _instance: new FontManager();}

    void Add(std::string path, std::string id, int size);
    void ClearID(std::string id);
    void Clear();
    
    void DrawAnimation();
    void SetLocalTime(std::string id, std::string text, SDL_Color color, float duration, int size, SDL_Rect source);

    TTF_Font* GetFont(std::string id);
    

private:
    FontManager() {};

private:

    std::map<std::string, TTF_Font*> _fontMap;
    static FontManager* _instance;
    
    int _localSize = 0;
    float _localTime = -1.f;
    std::string _text;
    std::string _localId;
    SDL_Color _color;
    SDL_Rect _localSource;
};