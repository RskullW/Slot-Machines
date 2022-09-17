#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Animation.h"

class AnimationSprite: public Animation
{
public:
    AnimationSprite(bool repeat = 1);

    virtual void Update(float dt);
    void Draw(float x, float y, int spritW, int spriH, float scaleX = 1.0f, float scaleY = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(std::string textureID, int sRow, int fCount, int animSpeed);

    void SetSpriteRow(int row);
    void IncrementSpriteRow();
    void DecrementSpriteRow();

    int GetCurFrame();
    int GetSpriteRow();

private:
    int _spriteRow, _speedAnim, _frameCount;
    std::string _textureID;
};


