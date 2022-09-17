#include "Slot.h"
#include "../Managers/TextureManager.h"
#include "../Controls/Input.h"


static int tempTime = 0;

static float RUN_FORCE = 0.25f;
static float JUMP_TIME = 8.0f;
static float JUMP_FORCE = 6.0f;


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
    
    _collider2D = new Collider2D();
    _collider2D->SetBuff(191, 186, 191, 186);

    _animation = new AnimationSprite();
    _animation->SetProps(textureID, 0, 0, 0);
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

    // Clicked
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LCTRL) && !isPlay)
    {
        if (_isRunning == 0)
        {
            //TODO: Добавить звук при вращении барабана тут или добавить в общий менеджер
            //SoundGame::GetInstance()->playEffect("attack", 2);
        }
    }
    

    // axis X
    _collider2D->Set(191, 186, 191, 186);
    
    AnimationState();
    _animation->Update(dt);
}

void Slot::AnimationState()
{

    _animation->SetProps("items", 1, 0, 0);
//  TODO: Добавить анимацию вращения слота
//    if (_isRunning)
//    {
//        _animation->SetProps("player", 5, 8, 380);
//    }

}