#include "PlantEnemy.h"
#include "Game.h"
#include "PlayScene.h"
#include "Bullet.h"

void CPlantEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

    CGameObject::Update(dt, coObjects);

    ULONGLONG now = GetTickCount64();
    CAnimations* animations = CAnimations::GetInstance();
    CAnimation* ani = animations->Get(ID_ANI_PLANT);

    int currentFrame = ani->GetCurrentFrameIndex();

    
    if (currentFrame == 2 && now - lastFireTime >= PLANT_BULLET_FIRE_INTERVAL)
    {
        FireBullet();
        lastFireTime = now;
    }
}

void CPlantEnemy::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(ID_ANI_PLANT)->Render(x, y);
}

void CPlantEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - PLANT_BBOX_WIDTH / 2;
    t = y - PLANT_BBOX_HEIGHT / 2;
    r = l + PLANT_BBOX_WIDTH;
    b = t + PLANT_BBOX_HEIGHT;
}

void CPlantEnemy::FireBullet()
{
    float bx = x;
    float by = y;

    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer(); 
    float mx, my;
    mario->GetPosition(mx, my);

    
    float dx = mx - bx;
    float dy = my - by;
    float length = sqrt(dx * dx + dy * dy);

    float speed = 0.08f; 
    float vx = speed * dx / length;
    float vy = speed * dy / length;

    CBullet* bullet = new CBullet(bx, by, vx, vy);
    scene->AddObject(bullet);
}