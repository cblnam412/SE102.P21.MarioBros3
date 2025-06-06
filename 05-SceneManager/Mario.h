#pragma once
#include "GameObject.h"

#include "Koopas.h"
#include "Animation.h"
#include "Animations.h"
#include"Teleport.h"
#include "GoalCard.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_END_SCENE 999 

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_BRING_RIGHT	650
#define ID_ANI_MARIO_BRING_LEFT	651

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_LEFT 5000
#define ID_ANI_MARIO_SMALL_HOLD_RIGHT 5001
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT 5002
#define ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT 5003

// ----- TAIL -----
#define ID_ANI_MARIO_TAIL_IDLE_LEFT		1700
#define ID_ANI_MARIO_TAIL_IDLE_RIGHT	1701
#define ID_ANI_MARIO_TAIL_WALKING_LEFT	1800
#define ID_ANI_MARIO_TAIL_WALKING_RIGHT 1801
#define ID_ANI_MARIO_TAIL_RUNNING_LEFT	1900
#define ID_ANI_MARIO_TAIL_RUNNING_RIGHT 1901
#define ID_ANI_MARIO_TAIL_BRACE_LEFT	2000
#define ID_ANI_MARIO_TAIL_BRACE_RIGHT	2001
#define ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT 2100
#define ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT 2101
#define ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT 2200
#define ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT 2201
#define ID_ANI_MARIO_TAIL_SIT_LEFT		2300
#define ID_ANI_MARIO_TAIL_SIT_RIGHT		2301
#define ID_ANI_MARIO_TAIL_KICK_LEFT		2400
#define ID_ANI_MARIO_TAIL_KICK_RIGHT	2401
#define ID_ANI_MARIO_TAIL_ATTACK_LEFT	2500
#define ID_ANI_MARIO_TAIL_ATTACK_RIGHT	2501
#define ID_ANI_MARIO_TAIL_HOLD_LEFT		2600
#define ID_ANI_MARIO_TAIL_HOLD_RIGHT	2601
#define ID_ANI_MARIO_TAIL_HOLD_WALK_LEFT 2602
#define ID_ANI_MARIO_TAIL_HOLD_WALK_RIGHT 2603
#define ID_ANI_MARIO_TAIL_FLYING_LEFT	2700
#define ID_ANI_MARIO_TAIL_FLYING_RIGHT	2701
#define ID_ANI_MARIO_TAIL_FALLING_LEFT	2800
#define ID_ANI_MARIO_TAIL_FALLING_RIGHT 2801
#define ID_ANI_MARIO_TAIL_LANDING_LEFT	2900
#define ID_ANI_MARIO_TAIL_LANDING_RIGHT 2901
#define ID_ANI_MARIO_TAIL_TRAVELLING	3000

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL 3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_TAIL_BBOX_WIDTH  16
#define MARIO_TAIL_BBOX_HEIGHT 27 // nhỏ hơn Big để tránh đuôi chạm đất
#define MARIO_TAIL_SITTING_BBOX_WIDTH  16
#define MARIO_TAIL_SITTING_BBOX_HEIGHT 19


#define MARIO_STATE_TAIL_ATTACK 700
#define MARIO_STATE_FLYING 800
#define MARIO_STATE_LANDING 220805
#define MARIO_STATE_FALLING 220806




#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isAttacking;
	BOOLEAN isHolding;
	BOOLEAN isHoldingJump;
	BOOLEAN isFlying;
	BOOLEAN isLanding;
	BOOLEAN isFalling;
    BOOLEAN isReadyToTeleport;
    BOOLEAN isTravelling;
    BOOLEAN isSlidingDownPipe;

	CKoopas* heldKoopas;
    Teleport* tlp;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	ULONGLONG attack_start;
	ULONGLONG fly_start;
	ULONGLONG landing_start;
	ULONGLONG falling_start;
    ULONGLONG travelling_start;
    ULONGLONG slidePause_start;
    ULONGLONG slideStartTime;

    ULONGLONG riseStartTime;

	BOOLEAN isOnPlatform;
	int coin; 
    int point;
    
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithParagoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e);
	void OnCollisionWithTeleport(LPCOLLISIONEVENT e);
	void OnCollisionWithLift(LPCOLLISIONEVENT e);
    void OnCollisionWithBrick(LPCOLLISIONEVENT e);
    void OnCollisionWithGoalCard(LPCOLLISIONEVENT e);
    void OnCollisionWithBoomerang(LPCOLLISIONEVENT e);
    void OnCollisionWithBoomerangBro(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTail();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isAttacking = false;
		isHolding = false;
		isFlying = false;
		isLanding = false;
		isFalling = false;
        isTravelling = false;

        isReadyToTeleport = false;
        isSlidingDownPipe = false;
       


		heldKoopas = nullptr;
        tlp = nullptr;

		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
        coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

    //Mario tuot xuong pipe
    void ShowCourseClearEffect();
    void TeleportToDestination();
    void StartSlideDownPipe();
    float slideTargetY = 0;
    float distance = abs(slideTargetY - slideStartY);
    float slideSpeed = distance / 2000.0f;


    //Mario trồi lên Pipe
    void StartRiseUpPipe();
    bool isRisingFromPipe = false;
    bool isReadyToRise = false;
    float riseStartY;
    float riseTargetY;
    int riseStep = 0;
    int slideStep = 0; 
    float slideStartY;
    bool isSlidingWait = false;
    bool isRisingWait = false;
    int card1 = -1;
    int card2 = -1;
    int card3 = -1;
    int cardCollected = -1;
    bool isAutoRunning = false;

    void ThrowKoopas();

    bool IsHolding() {
        return this->isHolding;
    }

    bool Dir() {
        return nx == -1;
    }


	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void updateKoopas(BOOLEAN isHolding);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetVX() { return vx; }



	int GetLevel() { return level; }
	void GetPosition(float& x, float& y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


	void SetHoldingJump(bool isHolding) { isHoldingJump = isHolding; }
	bool IsHoldingJump() const { return isHoldingJump; }
    bool IsReadyToTeleport() const { return isReadyToTeleport; }
    void StartTravelling() {
        isTravelling = true;
        travelling_start = GetTickCount64();
    }

    bool IsReadyToRise() const { return isReadyToRise; }
    bool GetIsSlidingWait() const { return isSlidingWait; }
    void SetSlidingWait(bool val) { isSlidingWait = val; }

    bool GetIsRisingWait() const { return isRisingWait; }
    void SetRisingWait(bool val) { isRisingWait = val; }

    void releaseKoopas() {
        isHolding = false;
        this->heldKoopas = nullptr;
    }

    bool isClearingCourse = false;
    bool IsClearingCourse() { return isClearingCourse; }
    void SetClearingCourse(bool value) { isClearingCourse = value; }
    bool IsAutoRunning() { return isAutoRunning; }
    void StartAutoRun() { isAutoRunning = true; }
    void StopAutoRun() { isAutoRunning = false; }

    int getCoins() {
        return this->coin;
    }
    int getPoint() {
        return this->point;
    }
};