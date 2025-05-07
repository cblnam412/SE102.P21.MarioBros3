#pragma once

#include "GameObject.h"

class CCloud : public CGameObject
{
protected:
    int length;				// Số lượng ô (1: mây đơn, 2: đôi, 3: ba)
    float cellWidth;
    float cellHeight;
    int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
    CCloud(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_begin, int sprite_id_middle, int sprite_id_end)
        : CGameObject(x, y)
    {
        this->length = length;
        this->cellWidth = cell_width;
        this->cellHeight = cell_height;
        this->spriteIdBegin = sprite_id_begin;
        this->spriteIdMiddle = sprite_id_middle;
        this->spriteIdEnd = sprite_id_end;
    }

    void Render() override;
    void Update(DWORD dt){}
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};
