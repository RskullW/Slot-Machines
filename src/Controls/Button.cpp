#include "Button.h"
#include "Input.h"

Button::Button(std::string textureID, int sourceH, int sourceW,
               int destH, int destW, int sourceX, int sourceY,
               int destX, int destY) {

    _texture = TextureManager::GetInstance()->GetTexture(textureID);

    _source.h = sourceH;
    _source.w = sourceW;
    _source.x = sourceX;
    _source.y = sourceY;

    _dest.h = destH;
    _dest.w = destW;
    _dest.x = destX;
    _dest.y = destY;

}

void Button::Update(Mouse &mouse) {
        if (SDL_HasIntersection(&_dest, &mouse.GetPoint()))
        {

            if (!_isSelectedFirst && !_isActive) {
//                soundGame::GetInstance()->playEffect("hover_menu", 0);
                _isSelectedFirst = true;
                _source.x = _source.w;
            }
            _isSelected = true;
        }

        else if (!_isActive) 
        {
            _isSelectedFirst = _isSelected = false;
            _source.x = 0;
        }
}

void Button::Draw(SDL_Renderer *rendererButton) {
    SDL_RenderCopy(rendererButton, _texture, &_source, &_dest);
}

void Button::Clean() {
    SDL_DestroyTexture(_texture);
}

void Button::SetNullButton() {
    _texture = nullptr;
}

SDL_Rect Button::GetSource() {
    return _source;
}
SDL_Rect Button::GetDest() {
    return _dest;
}
SDL_Texture* Button::GetTexture() {
    return _texture;
}

bool Button::GetActive() {
    return _isActive;
}

void Button::SetSourceX(int axisX) { 
    _source.x = axisX; 
}

void Button::SetSourceY(int axisY) { 
    _source.y = axisY; 
}

void Button::SetSourceW(int axisW) { 
    _source.w = axisW;
}
void Button::SetSourceH(int axisH) {
    _source.h = axisH;
}
void Button::SetSource(SDL_Rect newSource) {
    _source = newSource;
}

void Button::SetDestX(int axisX) { 
    _dest.x = axisX; 
}
void Button::SetDestY(int axisY) {
    _dest.y = axisY; 
}
void Button::SetDestW(int axisW) {
    _dest.w = axisW;
}
void Button::SetDestH(int axisH) {
    _dest.h = axisH;
}
void Button::SetDest(SDL_Rect newDest) {
    _dest = newDest;
}

bool Button::GetSelected() const {
    return _isSelected;
}

void Button::SetActive(bool isActive) {
    _isActive = isActive;
}
