#pragma once
#include <SDL2/SDL.h>
#include "../Managers/TextureManager.h"
#include "Mouse.h"

class Button
{
public:
    Button() {}

    Button(std::string textureID, int sourceH, int sourceW,
           int destH, int destW, int sourceX = 0, int sourceY = 0,
           int destX = 0, int destY = 0);

    void Update(Mouse& mouse);
    void Draw(SDL_Renderer* rendererButton);
    void Clean();
    void SetNullButton();

    SDL_Rect GetSource();
    SDL_Rect GetDest();
    SDL_Texture* GetTexture();
    
    bool GetActive();

    void SetSourceX(int axisX);
    void SetSourceY(int axisY);
    void SetSourceW(int axisW);
    void SetSourceH(int axisH);
    void SetSource(SDL_Rect newSource);
    
    void SetDestX(int axisX);
    void SetDestY(int axisY);
    void SetDestW(int axisW);
    void SetDestH(int axisH);
    void SetDest(SDL_Rect newDest);

    void SetActive(bool isActive = false);

    bool GetSelected() const;
private:
    bool _isSelected = false;
    bool _isSelectedFirst = false;
    bool _isActive = false;
    SDL_Texture* _texture;
    SDL_Rect _source, _dest;
};