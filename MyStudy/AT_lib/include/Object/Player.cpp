#include "Player.h"
#include "../Resources/Texture.h"
#include "../Core/Input.h"
#include <cassert>
#include "../../CAnimation.h"

CPlayer::CPlayer()
{};
CPlayer::~CPlayer() noexcept
{}
CPlayer::CPlayer(const CPlayer& Player) : 
	CMoveObj(Player){}

bool CPlayer::Init(){
	SetPos(878.f, 1300); 
	SetSize(250.f,224.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f); 

	SetTexture(L"Player", L"Animation/Player/Left/DEAD.bmp");
	SetColorKey(255, 0, 255);

	//SetCorrectionRenderToCollision(RECTANGLE{110,54,151,128});

	m_iHP = 1000;
	SetPhysics(true);
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation(L"PlayerAnimation");

	AddAnimationClip(L"IdleRight", AT_ATLAS, AO_LOOP,
		0.3f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerIdleRight", L"Animation\\Player\\Left\\IDLE1.bmp");

	SetAnimationClipColorkey(L"IdleRight",
		255, 0, 255);

	SAFE_RELEASE(pAni);

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime); 
	
	if (KEYPRESS("MoveFront")) {
	 //	MoveYFromSpeed(fDeltaTime, MD_BACK);
	}
	if (KEYPRESS("MoveBack")) {
	//	MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}
	if (KEYPRESS("MoveLeft")) {
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}
	if (KEYPRESS("MoveRight")) {
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}
	//if (KEYDOWN("Fire")) {
	//	Fire(); 
	//}
	if (KEYDOWN("Skill1")) {
		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
	}
	if (KEYUP("Jump") ) {
		if(bJump==false) 
		Pow.top = 600.f;
		/*if (bJump ==true) {
			Pow.top = 0.f;
		}*/
		bJump = true;
	}


}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	
	if (Pow.right > 0) {
		m_tPos.x += Pow.right * fDeltaTime;
		Pow.right -= Pow.right * fDeltaTime;

	}
	
	if (Pow.left > 0) {
		m_tPos.x -= Pow.left * fDeltaTime;
		Pow.left -= Pow.left * fDeltaTime;
	}
	
	if (Pow.top > 0) {
		m_tPos.y -= Pow.top * fDeltaTime;
		Pow.top -= Pow.top * fDeltaTime;
	}
	if (Pow.bottom > 0) {
		m_tPos.y += Pow.bottom * fDeltaTime;
		Pow.bottom -= Pow.bottom * fDeltaTime;
	}
	

	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	return CMoveObj::LateUpdate(fDeltaTime);
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
};

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
	wchar_t strHP[32] = {};
	wsprintf(strHP, L"HP : %d", m_iHP);
	POSITION Pos =GetCollisionPos();

	TextOut(hDC, Pos.x, Pos.y,
		strHP, lstrlen(strHP));

	//Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}
CPlayer* CPlayer::Clone()
{
	return new CPlayer{ *this };
}
void CPlayer::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj(L"Bullet",
		L"PlayerBullet",m_pLayer);

	POSITION tPos;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	//tPos.y = m_tPos.y + (0.5f - m_tPivot.y) * m_tSize.y;

	pBullet->SetPos(tPos);

	SAFE_RELEASE(pBullet); 
}
void CPlayer::Hit(CObj* const Target, float fDeltaTime)
{
	CObj::Hit(Target, fDeltaTime);

	if(Target->GetTag()==L"MushroomBullet")
	m_iHP -= 5;

	// 그라운드 충돌
	else if (Target->GetTag() == L"StageColl") {
		Pow.top = 0; 
		ClearGravity(); 
		bJump = false; 
	}
};

