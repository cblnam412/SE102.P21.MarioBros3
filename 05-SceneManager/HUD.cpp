#include "HUD.h"
#include "Game.h"
#include "Sprites.h"
#include "PlayScene.h"
#include "Mario.h"
#include <string.h>

void CHUB::Render(){
    CSprites* s = CSprites::GetInstance();

    s->Get(ID_HUD_FRAME)->Draw(x, y);

    RenderNumber(coins, x + 60, y - 3, 2); 
    RenderNumber(3, x - 43, y + 5, 2);

    RenderNumber(0, x - 20, y + 5, 7);
    RenderNumber(timeLeft, x + 52, y + 5, 3);
    RenderNumber(1, x - 35, y - 3, 1);
}

void CHUB::RenderNumber(int number, float x, float y, int digits) {
    CSprites* s = CSprites::GetInstance();
    string t = "";
    while (number > 0) {
        t = (char)(number % 10 + '0') + t;
        number /= 10;
    }
    while (t.length() < digits) t = '0' + t;

    for (int i = 0; i < digits; i++) {
        int digit = (int)(t[i] - '0');
        if (digit < 0 || digit > 9)
            return;
        s->Get(ID_NUMBER_0 + digit)->Draw(x + i * 8, y);
    }
}

void CHUB::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    
    CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)current_scene->GetPlayer();
    float cx, cy;
    mario->GetPosition(cx, cy);

    CGame* game = CGame::GetInstance();
    x = cx - game->GetBackBufferWidth() / 2 + 80;
    //y = cy - game->GetBackBufferHeight() / 2 + 340;
    y = 362;
    if (x < 80.0f)
        x = 80.0f;

    coins = mario->getCoins();

    ULONGLONG now = GetTickCount64();
    if (now - timeNow >= 1000) {
        timeNow = now, timeLeft--;
        if (timeLeft <= 0)
            mario->SetState(MARIO_STATE_DIE);
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CHUB::GetBoundingBox(float& l, float& t, float& r, float& b) {
    l = x;
    t = y;
    r = l;
    b = t;
}