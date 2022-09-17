#include "Background.h"
#include "TextureManager.h"

void Background::Draw(SDL_Renderer *renderer) {
    this->Object::Draw(renderer);
}

void Background::Clean() {
    this->Object::Clean();
}

Background::Background(std::string textureID, int sourceH, int sourceW, int destH, int destW, int srcX, int srcY,
                       int destX, int destY): Object(textureID, sourceH, sourceW, destH, destW) {
    _source.x = srcX;
    _source.y = srcX;
    _dest.x = destX;
    _dest.y = destY;
};