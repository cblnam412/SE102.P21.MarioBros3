#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include <string.h>

#define ID_HUD_FRAME    210000
#define ID_HUD_WORLD    210001
#define ID_TRIANGLE_ON  210010
#define ID_TRIANGLE_OFF 210011
#define ID_HUD_M    210001
#define ID_NUMBER_0 210020
#define ID_NUMBER_1 210021
#define ID_NUMBER_2 210022
#define ID_NUMBER_3 210023
#define ID_NUMBER_4 210024
#define ID_NUMBER_5 210025
#define ID_NUMBER_6 210026
#define ID_NUMBER_7 210027
#define ID_NUMBER_8 210028
#define ID_NUMBER_9 210029

class CHUB : public CGameObject {
protected:
    int coins;
    int lives;
    int score;
    int speedLevel;
    int world;
    int timeLeft;
    ULONGLONG timeNow = 0;
public:
    CHUB(float x, float y) : CGameObject(x, y) {
        this->timeLeft = 300;
    };

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();

    void GetBoundingBox(float& l, float& t, float& r, float& b);

    void RenderNumber(int number, float x, float y, int digits);

    void SetLives(int l) { lives = l; }
    void SetScore(int s) { score = s; }
    void SetSpeedLevel(int level) { speedLevel = level; }
    void SetWorld(int w) { world = w; }
    void SetTime(int t) { timeLeft = t; }

};