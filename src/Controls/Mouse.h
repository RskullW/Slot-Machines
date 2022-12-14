#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../Managers/TextureManager.h"

class Mouse {
public:
    Mouse() {}

    Mouse(std::string textureID) {
        _texture = TextureManager::GetInstance()->GetTexture(textureID);
        _rect.w = _rect.h = 25;
        _point.w = _point.h = 25;

        SDL_ShowCursor(false);
    }

    SDL_Rect &GetPoint() { return _point; }

    void Update() {
        SDL_GetMouseState(&_rect.x, &_rect.y);
        _point.x = _rect.x;
        _point.y = _rect.y;
    }
    
    void Draw(SDL_Renderer *_rendererMouse) {
        SDL_RenderCopy(_rendererMouse, _texture, nullptr, &_rect);
    }
    
    void Clean() {
        SDL_DestroyTexture(_texture);
    }

public:
    SDL_Texture *_texture;
    SDL_Rect _rect, _point;
};