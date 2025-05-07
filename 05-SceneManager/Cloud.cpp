#include "Cloud.h"
#include "Sprites.h"

void CCloud::Render()
{
    if (this->length <= 0) return;

    float xx = x;
    CSprites* s = CSprites::GetInstance();

    
    s->Get(this->spriteIdBegin)->Draw(xx, y);
    xx += this->cellWidth;

    
    for (int i = 1; i < this->length - 1; i++)
    {
        s->Get(this->spriteIdMiddle)->Draw(xx, y);
        xx += this->cellWidth;
    }

   
    if (length > 1)
        s->Get(this->spriteIdEnd)->Draw(xx, y);

    
}

void CCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    
    l = 0;
    t = 0;
    r = 0;
    b = 0;
}
