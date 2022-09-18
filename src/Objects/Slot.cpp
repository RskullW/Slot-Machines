#include "Slot.h"
#include "../Managers/TextureManager.h"
#include "../Managers/SoundsManager.h"
#include "../Managers/GameManager.h"
#include "../Controls/Input.h"
#include "thread"

#define ROTATE_SPEED_IN_FRAME 10000
#define SPEED 17.0f
#define SIZE_WIDTH_FIGURES 334

void Rotate(SDL_Rect *source, SDL_Rect *dest);

Slot::Slot(std::string textureID, int sourceH, int sourceW,
           int destH, int destW, int sourceX, int sourceY,
           int destX, int destY): 
           Object(textureID, sourceH, sourceW, destH, destW)
{
    
    _source.x = sourceX;
    _source.y = sourceY;
    
    _dest.x = destX;
    _dest.y = destY;
    _textureID = textureID;

    _animation = new AnimationSprite();
    _animation->SetProps(textureID, 1, 1, 1);
    
    _isRunning = false;
    _speed = SPEED;
}

void Slot::Draw(SDL_Renderer* renderer)
{
    this->Object::Draw(renderer);
}


void Slot::Clean()
{
    TextureManager::GetInstance()->Drop(_textureID);
}

void Slot::Update(float dt)
{
    _animation->Update(dt);
    
    if (_isRunning) {
        
        if (_timeRunning > 0 && _speed > 0) {
            _timeRunning-=1;

            if (_timeRunning > ROTATE_SPEED_IN_FRAME-40) {
                _source.y -= (int)_speed;
            }
            
            else {
                _source.y += (int) _speed;
            }
            
            if (((int)_timeRunning%100) == 0) {
                _speed-=1.f;
            } 
            
            if (_source.y >= 3000 || _source.y <= 0) {
                _source.y = 0;
            }
        }
        
        else {
            CorrectPositionSlots();
        }
    }
    
}

void Slot::StartRotate() {
    _isRunning = true;
    _timeRunning = (int)((ROTATE_SPEED_IN_FRAME-500) + rand() % ((ROTATE_SPEED_IN_FRAME) - (ROTATE_SPEED_IN_FRAME-500)));

    if ((_timeRunning < (ROTATE_SPEED_IN_FRAME-500) )|| (_timeRunning > ROTATE_SPEED_IN_FRAME)) {
        _timeRunning = rand()%200+1500;
    }

}

void Slot::CorrectPositionSlots() {
    if (_source.y % 337 != 0) {
        if (_source.y%337 > 337/2) {
            _source.y+= (337-_source.y%337);
        }

        else {
            _source.y -= _source.y %337;
        }

    }

    FindIndexFigure();
    _speed = SPEED;
    _isRunning = false;

    GameManager::GetInstance()->ProccessGame(false);
}

int Slot::GetIndexFigure() {
    return _indexFigure;
}

void Slot::FindIndexFigure() {
    int maxValue = _source.y;
    _indexFigure = 0;

    while (maxValue > SIZE_WIDTH_FIGURES) {
        maxValue-=SIZE_WIDTH_FIGURES;
        _indexFigure++;
    } 
    
    if (_indexFigure == 9) {
        _indexFigure = 0;
    }
}

void Slot::StopRotate() {
    if (_isRunning && _speed >= 10.f) {
        _speed = 10.f;
    } 
}