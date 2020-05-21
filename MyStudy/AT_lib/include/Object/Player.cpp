#include "Player.h"
#include "../Resources/Texture.h"
CPlayer::CPlayer()
{

}

CPlayer::~CPlayer() noexcept
{
}
CPlayer::CPlayer(const CPlayer& Player) : 
	CMoveObj(Player){}

bool CPlayer::Init(){
	SetPos(0.f, 3000.f); 
	SetSize(74.f,75.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f); 

	SetTexture(L"Player", L"Avatar.bmp");
	m_pTexture->SetColorKey(RGB(255, 0, 255));

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime); 

	if (GetAsyncKeyState('W') & 0x8000) {
		MoveYFromSpeed(fDeltaTime, MD_BACK);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		Fire(); 
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	return CMoveObj::LateUpdate(fDeltaTime);
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

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
;

