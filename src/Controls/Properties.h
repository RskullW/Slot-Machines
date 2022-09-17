#pragma once

#include <string>
#include <SDL2/SDL_render.h>

struct Properties
{
    std::string TextureID;
    int W, H;
    float X, Y;
    SDL_RendererFlip Flip;

    Properties(std::string texture, int x, int y, int w, int h, SDL_RendererFlip argFlip = SDL_FLIP_NONE)
    {
        TextureID = texture;
        X = x;
        Y = y;
        W = w;
        H = h;
        Flip = argFlip;
    }
};