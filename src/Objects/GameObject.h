#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "../Interfaces/IObject.h"
#include "../Controls/Transform.h"
#include "../Controls/Pointer.h"
#include "../Controls/Properties.h"

class GameObject:
        public IObject
{
public:
    GameObject(Properties* props) : _textureID(props->TextureID), _width(props->W), _height(props->H), _flip(props->Flip)
    {
        _transform = new Transform(props->X, props->Y);

        float px = (props->X + props->W) / 2;
        float py = (props->Y + props->H) / 2;
        _origin = new Pointer(px, py);
    }

    inline Pointer* GetOrigin() { return _origin; }
    virtual void Draw() = 0;
    virtual void Update(float temp) = 0;
    virtual void Clean() = 0;
    
protected:
    Pointer* _origin;
    Transform* _transform;
    int _width, _height;
    std::string _textureID;
    SDL_RendererFlip _flip;
};
