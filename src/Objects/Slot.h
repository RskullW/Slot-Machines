#pragma once

#include <mutex>
#include <thread>
#include "../Abstract classes/SlotAbstract.h"
#include "../Controls/Collider2D.h"
#include "../Animations/AnimationSprite.h"
#include "../Controls/RigidBody.h"
#include "Object.h"

class Slot final: public Object  {

public:
    Slot(std::string textureID, int sourceH, int sourceW,
         int destH, int destW, int sourceX = 0, int sourceY = 0,
         int destX = 0, int destY = 0);

    void Draw(SDL_Renderer* renderer) override;
    void Clean() override;
    void Update(float dt);
    
    void StartRotate();
    void StopRotate();
    int GetIndexFigure();

private:

    void AnimationState();
    void CorrectPositionSlots();
    void FindIndexFigure();
    
    bool _isRunning, isPlay;
    
    float _timeRunning;
    float _speed;
    int _indexFigure;
    
    std::thread* thread;
    std::string _textureID;
    Collider2D *_collider2D;
    AnimationSprite *_animation;
};