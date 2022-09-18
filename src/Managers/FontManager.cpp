#include "FontManager.h"
#include "GameManager.h"
#include "../Controls/Timer.h"
#include <iostream>


FontManager* FontManager::_instance = nullptr;

void FontManager::Add(std::string path, std::string id, int size) {

    if (TTF_Init()!=0)
    {
        std::cout << TTF_GetError() << '\n';
        return;
    }

    TTF_Font* p_Font = TTF_OpenFont(path.c_str(), size);

    if (p_Font == NULL)
    {
        std::cout << TTF_GetError() << " Path: " << path << '\n';
        return;
    }

    _fontMap[id] = p_Font;
}

void FontManager::ClearID(std::string id) {
    _fontMap.erase(id);
}

void FontManager::Clear(){
    _fontMap.clear();
}

TTF_Font* FontManager::GetFont(std::string id)
{
    if (_fontMap[id] == nullptr)
    {
        throw -1;
    }

    return _fontMap[id];
}

void FontManager::DrawAnimation() {

    if (_localTime <= 0.f) {
        return;
    }
    
    SDL_Color colorBackground = {0, 0, 0, 1};
    
    _localSource.y--;
    _localSource.x--;

    TTF_SetFontSize(GetFont(_localId), _localSize++);
    TTF_SetFontStyle(GetFont(_localId), TTF_STYLE_NORMAL);

    SDL_Surface *surface = TTF_RenderText_Shaded(GetFont(_localId), _text.c_str(),
                                                 _color, colorBackground);

    if (surface == nullptr) {
        SDL_Log("Error! Font do not exist, surface not loaded...");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(GameManager::GetInstance()->GetRenderer(), surface);

    if (texture == nullptr) {
        SDL_Log("Error! Font do not exist, texture not loaded...");
    }

    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &_localSource.w, &_localSource.h);
    SDL_RenderCopy(GameManager::GetInstance()->GetRenderer(), texture, NULL, &_localSource);

    _localTime-= Timer::GetInstance()->GetDeltaTime();
    
}

void FontManager::SetLocalTime(std::string id, std::string text, SDL_Color color, float duration, int size, SDL_Rect source) {
    _localId = id;
    _text = text;
    _color = color;
    _localTime = duration;
    _localSize = size;
    _localSource = source;
}