#include "Cloud.h"
#include "Sprites.h"

void CCloud::Render()
{
    if (this->length <= 0) return;

    float xx = x;
    CSprites* s = CSprites::GetInstance();

    // Vẽ sprite bắt đầu
    s->Get(this->spriteIdBegin)->Draw(xx, y);
    xx += this->cellWidth;

    // Vẽ phần thân (middle)
    for (int i = 1; i < this->length - 1; i++)
    {
        s->Get(this->spriteIdMiddle)->Draw(xx, y);
        xx += this->cellWidth;
    }

    // Vẽ sprite kết thúc
    if (length > 1)
        s->Get(this->spriteIdEnd)->Draw(xx, y);

    // Cloud là vật thể trang trí, không cần bounding box
}

void CCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    // Nếu cần check va chạm (hiếm khi), bạn giữ lại, còn không thì cho r = l = 0
    l = 0;
    t = 0;
    r = 0;
    b = 0;
}
