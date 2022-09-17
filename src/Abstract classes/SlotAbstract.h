#pragma once
#include "../Controls/Properties.h"
#include "../Objects/GameObject.h"

class SlotAbstract:
        public GameObject
{
public:
    SlotAbstract();
    SlotAbstract(Properties* props) : GameObject(props) {}

    virtual void Draw() = 0;
    virtual void Clean() = 0;
    virtual void Update(float dt) = 0;
    
protected:
    std::string _name;
};