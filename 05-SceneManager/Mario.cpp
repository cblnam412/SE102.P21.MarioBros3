#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Mushroom.h"
#include "Koopas.h"
#include "Leaf.h"
#include "Collision.h"
#include "PlantEnemy.h"
#include "Bullet.h"
#include "Paragoomba.h"
#include "BrickQuestion.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (isAttacking && GetTickCount64() - attack_start > 300)
	{
		isAttacking = false;
	}

	updateKoopas(isHolding);

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}
		
		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CCoin*>(e->obj))
			OnCollisionWithCoin(e);
		else if (dynamic_cast<CPortal*>(e->obj))
			OnCollisionWithPortal(e);
		else if (dynamic_cast<CMushroom*>(e->obj))
			OnCollisionWithMushroom(e);
		else if (dynamic_cast<CKoopas*>(e->obj))
			OnCollisionWithKoopas(e);
		else if (dynamic_cast<CLeaf*>(e->obj))
			OnCollisionWithLeaf(e);
		else if (dynamic_cast<CPlantEnemy*>(e->obj))
			OnCollisionWithPlant(e);
		else if (dynamic_cast<CBullet*>(e->obj))
			OnCollisionWithBullet(e);
		else if (dynamic_cast<CParagoomba*>(e->obj))
			OnCollisionWithParagoomba(e);
		else if (dynamic_cast<CBrickQuestion*>(e->obj))
			OnCollisionWithBrickQuestion(e);

		
}


void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if (koopas->GetState() == KOOPAS_STATE_SHELL || koopas->GetState() == KOOPAS_STATE_RELIVE) 
	{
		if (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT) {
			if (isHolding == false) {
				isHolding = true;
				heldKoopas = koopas;
			}
		}
		else {
			koopas->SetState(KOOPAS_STATE_ROTATE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (e->nx < 0) {
				koopas->setVX(KOOPAS_ROTATE_SPEED);
			}
		}
	}
	else if (e->ny < 0)
	{
		if (koopas->GetState() != KOOPAS_STATE_SHELL)
		{
			koopas->SetState(KOOPAS_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else 
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_SHELL)
			{
				if (isHolding == true) {
					updateKoopas(false);
				}
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}


void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	
	if (isAttacking && goomba->GetState() != GOOMBA_STATE_DIE)
	{
		float dx = goomba->GetX() - x;
		float dy = goomba->GetY() - y;

		if (abs(dx) <= 20 && abs(dy) <= 16) 
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			return;
		}
	}

	
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0 && goomba->GetState() != GOOMBA_STATE_DIE)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}


void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level < MARIO_LEVEL_TAIL) {
		SetLevel(MARIO_LEVEL_TAIL);
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e) {
	e->obj->Delete();
	if (level < MARIO_LEVEL_BIG) {
		SetLevel(MARIO_LEVEL_BIG);
	}
}

void CMario::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e) {

	CBrickQuestion* brickquestion = dynamic_cast<CBrickQuestion*>(e->obj);
	
	if (e -> ny > 0 && brickquestion->getnOBbj() > 0) {
		brickquestion->decnObj();

		if (brickquestion->getType() == 1)
		{
			if (level < MARIO_LEVEL_BIG)
				brickquestion->sMushroom();
			else brickquestion->sLeaf();
		}
		else if (brickquestion->getType() == 0) {
			brickquestion->sCoin();
		}
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}


void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	if (untouchable != 0) return;

	if (level == MARIO_LEVEL_TAIL)
	{
		SetLevel(MARIO_LEVEL_BIG);
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_SMALL);
		StartUntouchable();
	}
	else // MARIO_LEVEL_SMALL
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}


void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	if (untouchable)
	{
		return;
	}
	if (level == MARIO_LEVEL_TAIL)
	{
		SetLevel(MARIO_LEVEL_BIG);
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_SMALL);
		StartUntouchable();
	}
	else
	{
		SetState(MARIO_STATE_DIE);
	}
}


void CMario::OnCollisionWithParagoomba(LPCOLLISIONEVENT e)
{
	CParagoomba* paragoomba = dynamic_cast<CParagoomba*>(e->obj);

	if (!paragoomba || paragoomba->GetState() == PARAGOOMBA_STATE_DIE) return;

	// Mario nhảy từ trên xuống đầu Paragoomba
	if (e->ny < 0)
	{
		paragoomba->SetState(PARAGOOMBA_STATE_DIE);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // Mario bị đụng ngang bởi Paragoomba
	{
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE by Paragoomba >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}



//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


int CMario::GetAniIdTail()
{
	int aniId = -1;

	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT;
		}
	}
	else
	{
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TAIL_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_TAIL_SIT_LEFT;
		}
		else if (vx == 0)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
			else
				aniId = ID_ANI_MARIO_TAIL_IDLE_LEFT;
		}
		else if (vx > 0)
		{
			if (ax < 0)
				aniId = ID_ANI_MARIO_TAIL_BRACE_RIGHT;
			else if (ax == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_TAIL_RUNNING_RIGHT;
			else if (ax == MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_TAIL_WALKING_RIGHT;
		}
		else // vx < 0
		{
			if (ax > 0)
				aniId = ID_ANI_MARIO_TAIL_BRACE_LEFT;
			else if (ax == -MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_TAIL_RUNNING_LEFT;
			else if (ax == -MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_TAIL_WALKING_LEFT;
		}
	}

	
	if (isAttacking)
	{
		aniId = (nx > 0) ? ID_ANI_MARIO_TAIL_ATTACK_RIGHT : ID_ANI_MARIO_TAIL_ATTACK_LEFT;
	}

	if (aniId == -1)
		aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;

	return aniId;
}



//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TAIL)
		aniId = GetAniIdTail();

	animations->Get(aniId)->Render(x, y);
	
	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_TAIL_ATTACK:
		if (level == MARIO_LEVEL_TAIL)
		{
			isAttacking = true;
			attack_start = GetTickCount64(); // Để dừng sau 300ms chẳng hạn
		}
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}

	if (level == MARIO_LEVEL_TAIL)
	{
		if (isSitting)
		{
			left = x - MARIO_TAIL_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_TAIL_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_TAIL_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_TAIL_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_TAIL_BBOX_WIDTH / 2;
			top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
			right = left + MARIO_TAIL_BBOX_WIDTH;
			bottom = top + MARIO_TAIL_BBOX_HEIGHT;
		}
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}


void CMario::GetPosition(float& x, float& y)
{
	x = this->x;
	y = this->y;
}

void CMario::updateKoopas(BOOLEAN isHolding) {
	if (isHolding == false) {
		this->isHolding = isHolding;
		heldKoopas = nullptr;
		return;
	}
	this->heldKoopas->setAY(0);

	float tx = x + 16;
	if (state == MARIO_STATE_RUNNING_LEFT)
		tx = x - 16;

	this->heldKoopas->setXY(tx, y);
}