﻿#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    if (mario->IsAutoRunning())
        return;
	switch (KeyCode)
	{
    case DIK_DOWN:
    {
        if (mario->IsReadyToTeleport())
        {
            mario->SetSlidingWait(true); 
        }
        else
        {
            mario->SetState(MARIO_STATE_SIT);
        }
        break;
    }
    case DIK_S:
    {
        if (mario->IsReadyToRise())
        {
            mario->SetRisingWait(true); 
        }
        else
        {
            mario->SetState(MARIO_STATE_JUMP);
            if (mario->GetLevel() == MARIO_LEVEL_TAIL && abs(mario->GetVX()) >= MARIO_RUNNING_SPEED)
            {
                mario->SetState(MARIO_STATE_FLYING);
            }
        }
        break;
    }
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	case DIK_Q:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
			mario->SetState(MARIO_STATE_TAIL_ATTACK);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    if (mario->IsAutoRunning())
        return;
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
    case DIK_A:
        if (mario->IsHolding()) {
            mario->ThrowKoopas(); 
        }
        break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    if (mario->IsAutoRunning())
        return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
	mario->SetHoldingJump(game->IsKeyDown(DIK_S));
}