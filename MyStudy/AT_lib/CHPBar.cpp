#include "CHPBar.h"
#include "include/Object/MoveObj.h"
#include "include/CCore.h"
#include <string>
bool CHPBar::Init()
{
    return true;
};

CHPBar* CHPBar::Clone()
{
    return new CHPBar{ *this };
};

void CHPBar::Render(HDC hDC, float fDeltaTime)
{
    CUI::Render(hDC, fDeltaTime);
    if (Owner == nullptr)return;

    int CurrentOwnerLevel = 0;
        CurrentOwnerLevel = Owner->Level;

    if (Owner->GetTag() == L"Player")
    {
        SetTextColor(hDC, RGB(255, 255, 255));
        SetBkMode(hDC, TRANSPARENT);
        LONG X = 0 + 40;
        LONG Y = (LONG)GET_SINGLE(CCore)->GetResolution().iH - 53 / 2;
        LONG Size = 50;
        RECT rt = RECT{ X,Y,X + Size,Y + Size };
        DrawText(hDC, std::to_wstring(CurrentOwnerLevel).c_str(), -1, &rt, DT_LEFT | DT_VCENTER);
    }
}

