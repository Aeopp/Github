#include "Rope.h"
#include <algorithm>
#include "include/Object/MoveObj.h"
#include "include/Object/Player.h"
#include <iostream>
#include "include/Core/Input.h"
bool CRope::Init()
{
    return true;
}

void CRope::Input(float fDeltaTime)
{
    CObj::Input(fDeltaTime);
};

int CRope::Update(float fDeltaTime)
{
    CObj::Update(fDeltaTime);
    return 0;
};

int CRope::LateUpdate(float fDeltaTime)
{
    CObj::LateUpdate(fDeltaTime);

    return 0;
};

void CRope::Collision(float fDeltaTime)
{
    CObj::Collision(fDeltaTime);
};

void CRope::Hit(CObj* const Target, float fDeltaTime)
{
    CObj::Hit(Target, fDeltaTime);

    if (auto Player = dynamic_cast<CPlayer*>(Target); Player != nullptr&&
        (KEYDOWN("Up")||KEYDOWN("Down"))) {
        Player->bRope = true; 
        Player->m_tPos.x = m_tPos.x;
        Player->SetGravityTime(0.f);
        Player->MovePos.top = 0;
    }
    // Ÿ���� �÷��̾��� �����÷��׸� ���ش�
    // �÷��׸� ���� ���� �ڱ��ڽ� x��ǥ�� �÷��̾� x��ǥ�� �����Ѵ�.
    auto [x, y] = Target->GetPos();

   /* if (y <= GetPos().y) {
        if (auto IsMoveable = dynamic_cast<CMoveObj*>(Target); IsMoveable != nullptr) {
            if (IsMoveable->bJump != true) {
                Target->SetGravityTime(0.f);
                IsMoveable->MovePos.top = 0;
            }
        }
    }*/
}
void CRope::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
    CObj::ReleaseHitEvent(Target, fDeltaTime);

    if (auto Player = dynamic_cast<CPlayer*>(Target); Player != nullptr) {
        Player->bRope = false;
//        Player->m_tPos.x = m_tPos.x;
  //      Player->SetGravityTime(0.f);
    //    Player->MovePos.top = 0;
    }
}
;

void CRope::Render(HDC hDC, float fDeltaTime)
{
    CObj::Render(hDC, fDeltaTime);

};

CRope* CRope::Clone()
{
    return new CRope{ *this };
}
