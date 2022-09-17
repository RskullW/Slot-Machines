#pragma once

#include <string>
#include "SDL2/SDL.h"

class Object {
public:
    Object(std::string textureID, int sourceH, int sourceW, 
           int destH, int destW);
    virtual void Draw(SDL_Renderer* renderer);
    virtual void Clean();

protected:
    SDL_Rect _source, _dest;
    SDL_Texture* _texture;
};