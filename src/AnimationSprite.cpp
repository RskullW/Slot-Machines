#include "AnimationSprite.h"
#include "TextureManager.h"

AnimationSprite::AnimationSprite(bool repeat): Animation(repeat) {}

void AnimationSprite::Draw(float x, float y, int w, int h, float scaleX, float scaleY, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(_textureID, x, y, w, h, _spriteRow, _curFrame, flip);
}

void AnimationSprite::Update(float dt)
{
    _curFrame = (SDL_GetTicks() / _speedAnim) % _frameCount;
}

void AnimationSprite::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
    _speedAnim = speed;
    _textureID = textureID;
    _spriteRow = spriteRow;
    _frameCount = frameCount;
}

void AnimationSprite::SetSpriteRow(int row) { 
    _spriteRow = row; 
}

void AnimationSprite::IncrementSpriteRow() {
    _spriteRow++; 
}

void AnimationSprite::DecrementSpriteRow() { 
    _spriteRow--;
}

int AnimationSprite::GetCurFrame() { 
    return _curFrame; 
}

int AnimationSprite::GetSpriteRow() {
    return _spriteRow; 
}