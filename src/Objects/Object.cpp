#include <iostream>
#include "Object.h"
#include "../Managers/TextureManager.h"

Object::Object(std::string textureID, int sourceH, int sourceW,
               int destH, int destW) {
    _texture = TextureManager::GetInstance()->GetTexture(textureID);
    
    _source.h = sourceH;
    _source.w = sourceW;
    
    _dest.h = destH;
    _dest.w = destW;
    
    _source.x = _source.y = _dest.x = _dest.y = 0;
}

void Object::Draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, _texture, &_source, &_dest);
}

void Object::Clean() {
    SDL_DestroyTexture(_texture);
}