#pragma once

#include <string>

#include <SDL2/SDL_render.h>
#include "Object.h"

class Background: public Object{
public:
    Background(std::string textureID, int sourceH, int sourceW, int destH, int destW, int srcX = 0, int srcY = 0, int destX = 0, int destY = 0);
    void Draw(SDL_Renderer* renderer) override;
    void Clean() override;
};