#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000

#define ID_ANI_SWITCH          10001   
#define ID_ANI_SWITCH_HIT      10002

#define BRICK_STATE_NORMAL     0
#define BRICK_STATE_HITTED     1
#define BRICK_STATE_SHOW_SWITCH 2 

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
protected:
    int state = BRICK_STATE_NORMAL;
    bool hasSwitch = false;
    bool isHitted = false;
    bool isSwitchVisible = false;
    bool isSwitchPressed = false;

public:
    CBrick(float x, float y, bool hasSwitch = false);

    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    void SetState(int state);
    void SetSwitchPressed(bool pressed) { isSwitchPressed = pressed; }
    void SetHitted();
    bool HasSwitch() { return hasSwitch; }
};