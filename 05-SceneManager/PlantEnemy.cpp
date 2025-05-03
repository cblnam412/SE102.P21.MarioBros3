#include "PlantEnemy.h"

void CPlantEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

    CGameObject::Update(dt, coObjects);
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
