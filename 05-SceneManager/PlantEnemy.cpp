#include "PlantEnemy.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Bullet.h"
#include "debug.h"


void CPlantEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;

    if (type == PLANT_TYPE_SHOOTING_RED)
        UpdateShootinFlower();
    else if (type == PLANT_TYPE_CARNIVOURING_GREEN)
        UpdateGreenCarniFlower();
    else if (type == PLANT_TYPE_SHOOTING_GREEN)
        UpdateShootinFlower();

    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlantEnemy::UpdateShootinFlower()
{
    if (state == PLANT_STATE_REST && GetTickCount64() - rest_start > PLANT_REST_TIME)
    {
        enableToShoot = true;
        rest_start = 0;
    }

   
    if (state == PLANT_STATE_REST && enableToShoot)
    {
        SetState(PLANT_STATE_RISE_UP);
        
    }

    if (state == PLANT_STATE_ATTACK)
        AimAndShoot();

    if (y <= minY && state == PLANT_STATE_RISE_UP)
    {
        this->SetState(PLANT_STATE_ATTACK);
        this->y = minY;
       
    }

    if (y >= maxY)
    {
        this->SetState(PLANT_STATE_IN_TUBE);
        this->y = maxY;
        
    }
}




void CPlantEnemy::UpdateGreenCarniFlower()
{
    ULONGLONG now = GetTickCount64();

    if (state == PLANT_STATE_IN_TUBE)
    {
        if (now - rest_start > PLANT_REST_TIME)
        {
            SetState(PLANT_STATE_RISE_UP);
        }
    }
    else if (state == PLANT_STATE_RISE_UP)
    {
        if (y <= minY)
        {
            y = minY;
            SetState(PLANT_STATE_ATTACK); 
        }
    }
    else if (state == PLANT_STATE_ATTACK)
    {
        if (now - aim_start > PLANT_AIM_TIME)
        {
            SetState(PLANT_STATE_DIVE);
        }
    }
    else if (state == PLANT_STATE_DIVE)
    {
        if (y >= maxY)
        {
            y = maxY;
            vy = 0; 
            SetState(PLANT_STATE_IN_TUBE);
            rest_start = GetTickCount64();
        }
    
    }
}

void CPlantEnemy::OnNoCollision(DWORD dt)
{
    y += vy * dt;
}

void CPlantEnemy::Render()
{

   // if (IsWaiting && IsWaitable) return;
    CAnimations* animations = CAnimations::GetInstance();
    CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    int animation_ID = -1;

    if (type == PLANT_TYPE_SHOOTING_RED)
        animation_ID = GetAniID_Red();
    else if (type == PLANT_TYPE_CARNIVOURING_GREEN)
        animation_ID = GetAniID_Carni();
    else if (type == PLANT_TYPE_SHOOTING_GREEN)
        animation_ID = GetAniID_Green();

    if (animation_ID != -1)
        animations->Get(animation_ID)->Render(x, y);
}

int CPlantEnemy::GetAniID_Red()
{
    int aniID = -1;
    CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

    if (state == PLANT_STATE_RISE_UP)
    {
        if (mario->GetX() > x && mario->GetY() > y)
            aniID = ID_ANI_PLANT_RISE_UP_RIGHT;
        else if (mario->GetX() < x && mario->GetY() > y)
            aniID = ID_ANI_PLANT_RISE_UP_LEFT;
        else if (mario->GetX() < x && mario->GetY() <= y)
            aniID = ID_ANI_PLANT_RISE_UP_LEFT_FACE_UP;
        else
            aniID = ID_ANI_PLANT_RISE_UP_RIGHT_FACE_UP;
    }
    else if (state == PLANT_STATE_ATTACK)
    {
        if (mario->GetX() > x && mario->GetY() > y)
            aniID = ID_ANI_PLANT_SHOOT_RIGHT;
        else if (mario->GetX() < x && mario->GetY() > y)
            aniID = ID_ANI_PLANT_SHOOT_LEFT;
        else if (mario->GetX() < x && mario->GetY() <= y)
            aniID = ID_ANI_PLANT_SHOOT_LEFT_FACE_UP;
        else
            aniID = ID_ANI_PLANT_SHOOT_RIGHT_FACE_UP;
    }
    else if (state == PLANT_STATE_DIVE)
    {
        if (mario->GetX() > x && mario->GetY() > y)
            aniID = ID_ANI_PLANT_DIVE_RIGHT;
        else if (mario->GetX() < x && mario->GetY() > y)
            aniID = ID_ANI_PLANT_DIVE_LEFT;
        else if (mario->GetX() < x && mario->GetY() <= y)
            aniID = ID_ANI_PLANT_DIVE_LEFT_FACE_UP;
        else
            aniID = ID_ANI_PLANT_DIVE_RIGHT_FACE_UP;
    }
    return aniID;
}

int CPlantEnemy::GetAniID_Carni()
{
    return ID_ANI_PLANT_CARNIVOUR_RISE;
}


int CPlantEnemy::GetAniID_Green()
{
    int aniID = -1;
    CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

    if (state == PLANT_STATE_RISE_UP)
    {
        if (mario->GetX() > x && mario->GetY() > y)
            aniID = ID_ANI_GREEN_PLANT_RISE_UP_RIGHT;
        else if (mario->GetX() < x && mario->GetY() > y)
            aniID = ID_ANI_GREEN_PLANT_RISE_UP_LEFT;
        else if (mario->GetX() < x && mario->GetY() <= y)
            aniID = ID_ANI_GREEN_PLANT_RISE_UP_LEFT_FACE_UP;
        else
            aniID = ID_ANI_GREEN_PLANT_RISE_UP_RIGHT_FACE_UP;
    }
    else if (state == PLANT_STATE_ATTACK)
    {
        if (mario->GetX() > x && mario->GetY() > y)
            aniID = ID_ANI_GREEN_PLANT_SHOOT_RIGHT;
        else if (mario->GetX() < x && mario->GetY() > y)
            aniID = ID_ANI_GREEN_PLANT_SHOOT_LEFT;
        else if (mario->GetX() < x && mario->GetY() <= y)
            aniID = ID_ANI_GREEN_PLANT_SHOOT_LEFT_FACE_UP;
        else
            aniID = ID_ANI_GREEN_PLANT_SHOOT_RIGHT_FACE_UP;
    }
    else if (state == PLANT_STATE_DIVE)
    {
        if (mario->GetX() > x && mario->GetY() > y)
            aniID = ID_ANI_GREEN_PLANT_DIVE_RIGHT;
        else if (mario->GetX() < x && mario->GetY() > y)
            aniID = ID_ANI_GREEN_PLANT_DIVE_LEFT;
        else if (mario->GetX() < x && mario->GetY() <= y)
            aniID = ID_ANI_GREEN_PLANT_DIVE_LEFT_FACE_UP;
        else
            aniID = ID_ANI_GREEN_PLANT_DIVE_RIGHT_FACE_UP;
    }
    return aniID;
}

void CPlantEnemy::SetState(int state)
{
    if (this->state == PLANT_STATE_DIE) return;

    switch (state)
    {
    case PLANT_STATE_DIVE:
        vy = PLANT_RISE_SPEED;
        ay = 0;
        aim_start = 0;
        rest_start = GetTickCount64();

        break;

    case PLANT_STATE_RISE_UP:
        vy = -PLANT_RISE_SPEED;
        ay = 0;
        break;

    case PLANT_STATE_ATTACK:
        vy = 0;
        ay = 0;
        aim_start = 0;
        rest_start = GetTickCount64();

        break;

    case PLANT_STATE_REST:
        vy = 0;
        ay = 0;
        enableToShoot = false;

        break;

    case PLANT_STATE_DIE:
        this->Delete();
        HandleFlowerDeadEffect();

        break;
    }

    CGameObject::SetState(state);
}

void CPlantEnemy::HandleFlowerDeadEffect()
{
    die_start = GetTickCount64();

    CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

}
void CPlantEnemy::AimAndShoot()
{
    if (GetTickCount64() - aim_start >= PLANT_AIM_TIME)
    {
        if (type != PLANT_TYPE_CARNIVOURING_GREEN)
        {
            CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
            CMario* mario = (CMario*)current_scene->GetPlayer();

            CBullet* fire_bullet = new CBullet(this->x, this->y, 0, 0);
            fire_bullet->SetPosition(this->x, this->y - 2.0f);
            SetSpeedFireBullet(fire_bullet, mario);

            current_scene->AddObject(fire_bullet);
            DebugOut(L"[BULLET] Bullet added at (%.2f, %.2f)\n", x, y);
        }
        SetState(PLANT_STATE_DIVE);
    }
}
void CPlantEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    if (type == PLANT_TYPE_SHOOTING_RED)
    {
        l = x - PLANT_WIDTH / 2;
        t = y - PLANT_HEIGHT / 2;
        r = l + PLANT_WIDTH;
        b = t + PLANT_HEIGHT;
    }
    else
    {
        l = x - PLANT_WIDTH / 2;
        t = y - GREEN_PLANT_HEIGHT / 2;
        r = l + PLANT_WIDTH;
        b = t + GREEN_PLANT_HEIGHT;
    }
}

CBullet* CPlantEnemy::SetSpeedFireBullet(CBullet* bullet, CMario* mario)
{
    if (this->x <= mario->GetX() && this->y < mario->GetY())
        bullet->SetSpeed(BULLET_VX, BULLET_VY);
    else if (this->x > mario->GetX() && this->y > mario->GetY())
        bullet->SetSpeed(-BULLET_VX, -BULLET_VY);
    else if (this->x > mario->GetX() && this->y < mario->GetY())
        bullet->SetSpeed(-BULLET_VX, BULLET_VY);
    else if (this->x <= mario->GetX() && this->y > mario->GetY())
        bullet->SetSpeed(BULLET_VX, -BULLET_VY);

    return bullet;
}
