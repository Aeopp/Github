#include "Portal.h"
#include "include/Object/Player.h"
#include "include/Core/Input.h"
#include "include/Resources/Texture.h"
#include "include/Macro.h"
#include "CAnimation.h"
void Portal::Render(HDC hDC, float fDeltaTime)
{
	
	CObj::Render(hDC, fDeltaTime);
}

bool Portal::Init()
{
	SetPos(0.f, 0);
	SetSize(349.3f, 360.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetCorrectionRenderToCollision(RECTANGLE{ 100,100,100,100 });

	SetTexture(L"Portal", L"Portal.bmp");
	SetColorKey(255, 0, 255);

//	CAnimation* pAni = CreateAnimation(L"PortalAnim");
//
//	// TODO :: ANIMATION Field
//	// Idle 
//	{
//		AddAnimationClip(L"PortalAnimation", AT_ATLAS, AO_LOOP,
//			0.5f, 3, 3, 0, 0, 3, 3, 0.f, L"PortalAnimation", L"PortalAnim.bmp");
//		SetAnimationClipColorkey(L"PortalAnimation", 255, 0, 255);
//	}
////	m_pTexture->bAlpha = true; 
//
//	m_pAnimation->ChangeClip(L"PortalAnimation");
//	m_pAnimation->SetDefaultClip(L"PortalAnimation");

	return true; 
}

void Portal::Hit(CObj* const Target, float fDeltaTime)
{
	CObj::Hit(Target, fDeltaTime);

	if (Target->GetTag() == L"Player" && KEYUP("Portal")) {
		if (auto Player = dynamic_cast<CPlayer*>(Target); Player != nullptr) {
			Player->bPortal= true;
			PortalEvent();
		}
	}
}
void Portal::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	CObj::ReleaseHitEvent(Target, fDeltaTime);

	if (Target->GetTag() == L"Player") {
		if (auto Player = dynamic_cast<CPlayer*>(Target); Player != nullptr) {
			Player->bPortal = false;
		}
	}
}


