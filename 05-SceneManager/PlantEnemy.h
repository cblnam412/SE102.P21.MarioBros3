#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Bullet.h"
#include "PlayScene.h"



#define PLANT_TYPE_SHOOTING_RED 1
#define PLANT_TYPE_SHOOTING_GREEN 2
#define PLANT_TYPE_CARNIVOURING_GREEN 3

#define ATTACK_RANGE 90.0f
#define PLANT_RISE_SPEED 0.015f
#define PLANT_GRAVITY	0.0f

#define PLANT_REST_TIME 1500
#define PLANT_AIM_TIME 500

#define PLANT_WIDTH 16
#define PLANT_HEIGHT 32
#define GREEN_PLANT_HEIGHT 24


#define PLANT_STATE_IN_TUBE -1
#define PLANT_STATE_DIVE 0 
#define PLANT_STATE_RISE_UP 1 
#define PLANT_STATE_ATTACK 2
#define PLANT_STATE_REST 3
#define PLANT_STATE_DIE 4

#define ID_ANI_PLANT_RISE_UP_LEFT 181500
#define ID_ANI_PLANT_RISE_UP_RIGHT 181600
#define ID_ANI_PLANT_RISE_UP_LEFT_FACE_UP 181530    
#define ID_ANI_PLANT_RISE_UP_RIGHT_FACE_UP 181630
#define ID_ANI_PLANT_SHOOT_LEFT 181550
#define ID_ANI_PLANT_SHOOT_RIGHT 181650
#define ID_ANI_PLANT_SHOOT_LEFT_FACE_UP 181560
#define ID_ANI_PLANT_SHOOT_RIGHT_FACE_UP 181660
#define ID_ANI_PLANT_DIVE_LEFT	181700
#define ID_ANI_PLANT_DIVE_RIGHT 181750
#define ID_ANI_PLANT_DIVE_LEFT_FACE_UP	181710
#define ID_ANI_PLANT_DIVE_RIGHT_FACE_UP 181760

#define ID_ANI_PLANT_CARNIVOUR_RISE 181810

#define ID_ANI_GREEN_PLANT_RISE_UP_LEFT 182500
#define ID_ANI_GREEN_PLANT_RISE_UP_RIGHT 182600
#define ID_ANI_GREEN_PLANT_RISE_UP_LEFT_FACE_UP 182530    
#define ID_ANI_GREEN_PLANT_RISE_UP_RIGHT_FACE_UP 182630
#define ID_ANI_GREEN_PLANT_SHOOT_LEFT 182550
#define ID_ANI_GREEN_PLANT_SHOOT_RIGHT 182650
#define ID_ANI_GREEN_PLANT_SHOOT_LEFT_FACE_UP 182560
#define ID_ANI_GREEN_PLANT_SHOOT_RIGHT_FACE_UP 182660
#define ID_ANI_GREEN_PLANT_DIVE_LEFT	182700
#define ID_ANI_GREEN_PLANT_DIVE_RIGHT 182750
#define ID_ANI_GREEN_PLANT_DIVE_LEFT_FACE_UP	182710
#define ID_ANI_GREEN_PLANT_DIVE_RIGHT_FACE_UP 182760


class CPlantEnemy :public CGameObject
{
    float minY, maxY, ay;
    ULONGLONG aim_start, rest_start, die_start, attack_delay_start;
    BOOLEAN enableToShoot;
    int type;
public:
    CPlantEnemy()
    {
        minY = -1;
        maxY = -1;
        aim_start = 0;
        rest_start = 0;
        die_start = 0;
        attack_delay_start = 0;
        enableToShoot = true;
        type = -1;
        ay = PLANT_GRAVITY;
    };
    CPlantEnemy(float x, float y, int type) :CGameObject(x, y)
    {
        this->x = x;
        this->y = y;
        this->vy = 0;
        this->ay = PLANT_GRAVITY;

        this->type = type;
        if (type == PLANT_TYPE_SHOOTING_RED)
            minY = y - PLANT_HEIGHT - 8.0f;
        else if (type == PLANT_TYPE_SHOOTING_GREEN)
            minY = y - GREEN_PLANT_HEIGHT - 10.0f;
        else
            minY = y - GREEN_PLANT_HEIGHT;
        maxY = y;

        aim_start = 0;
        rest_start = 0;
        die_start = 0;
        enableToShoot = true;
        IsWaitable = true;

        rest_start = GetTickCount64();
        this->SetState(PLANT_STATE_IN_TUBE);
        

    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void SetState(int para);
    void AimAndShoot();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void UpdateShootinFlower();
    void UpdateGreenCarniFlower();

    void OnNoCollision(DWORD dt);

    int IsBlocking() { return 0; }
    void SetFlowerMinY(float min_Y) { this->minY = min_Y; }

    int GetAniID_Red();
    int GetAniID_Carni();
    int GetAniID_Green();
    void HandleFlowerDeadEffect();

    CBullet* SetSpeedFireBullet(CBullet* bullet, CMario* mario);
};