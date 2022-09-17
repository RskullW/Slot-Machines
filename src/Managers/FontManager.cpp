#include "FontManager.h"
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