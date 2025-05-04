#include "PlantEnemy.h"
#include "Game.h"
#include "PlayScene.h"
#include "Bullet.h"

void CPlantEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

    CGameObject::Update(dt, coObjects);

    ULONGLONG now = GetTickCount64();
    if (now - lastFireTime >= PLANT_BULLET_FIRE_INTERVAL)
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

    CBullet* bullet = new CBullet(bx, by, -0.05f, 0); // bay sang trái

    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    scene->AddObject(bullet);
}