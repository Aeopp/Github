#include "Player.h"
#include "../Resources/Texture.h"
#include "../Core/Input.h"
#include <cassert>
#include "../../CAnimation.h"
#include "../Scene/CScene.h"
#include "../CCore.h"
#include "../Collision/Colinder.h"
#include "Monster.h"
#include <numeric>
#include <algorithm>
CPlayer::CPlayer()
{};
CPlayer::~CPlayer() noexcept
{};

CPlayer::CPlayer(const CPlayer& Player) : 
	CMoveObj(Player){
	*this = Player;
}

void CPlayer::Attack()&
{
	m_bAttack = true; 
}

bool CPlayer::Init() {
	SetPos(0.f, 0);
	SetSize(250.f, 224.f);
	SetSpeed(200.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetCorrectionRenderToCollision(RECTANGLE{ 112,60,101,96});

	SetTexture(L"Player", L"Animation/Player/Left/DEAD.bmp");
	SetColorKey(255, 0, 255);

	//SetCorrectionRenderToCollision(RECTANGLE{110,54,151,128});

	m_iHP = 1000;
	SetPhysics(true);
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation(L"PlayerAnimation");

	// TODO :: ANIMATION Field
	// Idle 
	{
		AddAnimationClip(L"PlayerIdleRight", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerIdleRight", L"Animation\\Player\\Right\\IDLE1.bmp");
		SetAnimationClipColorkey(L"PlayerIdleRight", 255, 0, 255);

		AddAnimationClip(L"PlayerIdleLeft", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerIdleLeft", L"Animation\\Player\\Left\\IDLE1.bmp");
		SetAnimationClipColorkey(L"PlayerIdleLeft", 255, 0, 255);
	}
	//ROPE
	{
		AddAnimationClip(L"PlayerRope", AT_ATLAS, AO_ONCE_RETURN,
			1.0f, 1, 2, 0, 0, 1, 2, 0.f, L"PlayerRope", L"Animation\\Player\\Right\\ROPE.bmp");
		SetAnimationClipColorkey(L"PlayerRope", 255, 0, 255);
	}
	// Jump 
	{
		AddAnimationClip(L"PlayerJumpLeft", AT_ATLAS, AO_LOOP,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"PlayerJumpLeft", L"Animation\\Player\\Left\\JUMP.bmp");
		SetAnimationClipColorkey(L"PlayerJumpLeft", 255, 0, 255);

		AddAnimationClip(L"PlayerJumpRight", AT_ATLAS, AO_LOOP,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"PlayerJumpRight", L"Animation\\Player\\Right\\JUMP.bmp");
		SetAnimationClipColorkey(L"PlayerJumpRight", 255, 0, 255);
	}

	//Dead
	{
		AddAnimationClip(L"PlayerDeadLeft", AT_ATLAS, AO_LOOP,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"PlayerDeadLeft", L"Animation\\Player\\Left\\DEAD.bmp");
		SetAnimationClipColorkey(L"PlayerDeadLeft", 255, 0, 255);

		AddAnimationClip(L"PlayerDeadRight", AT_ATLAS, AO_LOOP,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"PlayerDeadRight", L"Animation\\Player\\Right\\DEAD.bmp");
		SetAnimationClipColorkey(L"PlayerDeadRight", 255, 0, 255);

	}

	// Walk
	{
		AddAnimationClip(L"PlayerWalkRight", AT_ATLAS, AO_ONCE_RETURN,
			0.7f, 1, 4, 0, 0, 1, 4, 0.f, L"PlayerWalkRight", L"Animation\\Player\\Right\\WALK.bmp");
		SetAnimationClipColorkey(L"PlayerWalkRight", 255, 0, 255);

		AddAnimationClip(L"PlayerWalkLeft", AT_ATLAS, AO_ONCE_RETURN,
			0.7f, 1, 4, 0, 0, 1, 4, 0.f, L"PlayerWalkLeft", L"Animation\\Player\\Left\\WALK.bmp");
		SetAnimationClipColorkey(L"PlayerWalkLeft", 255, 0, 255);
	}

	// battleIdle
	{
		AddAnimationClip(L"PlayerBattleIdleLeft", AT_ATLAS, AO_LOOP,
			0.3f, 1, 4, 0, 0, 1, 4, 0.f, L"PlayerBattleIdleLeft", L"Animation\\Player\\Left\\IDLE.bmp");
		SetAnimationClipColorkey(L"PlayerBattleIdleLeft", 255, 0, 255);

		AddAnimationClip(L"PlayerBattleIdleRight", AT_ATLAS, AO_LOOP,
			0.3f, 1, 4, 0, 0, 1, 4, 0.f, L"PlayerBattleIdleRight", L"Animation\\Player\\Right\\IDLE.bmp");
		SetAnimationClipColorkey(L"PlayerBattleIdleRight", 255, 0, 255);
	}

	// Swing1
	{
		AddAnimationClip(L"PlayerAttackLeft", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerAttackLeft", L"Animation\\Player\\Left\\SWING1.bmp");
		SetAnimationClipColorkey(L"PlayerAttackLeft", 255, 0, 255);

		AddAnimationClip(L"PlayerAttackRight", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerAttackRight", L"Animation\\Player\\Right\\SWING1.bmp");
		SetAnimationClipColorkey(L"PlayerAttackRight", 255, 0, 255);
	}

	// Swing2
	{
		AddAnimationClip(L"PlayerAttack2Left", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerAttack2Left", L"Animation\\Player\\Left\\SWING2.bmp");
		SetAnimationClipColorkey(L"PlayerAttack2Left", 255, 0, 255);

		AddAnimationClip(L"PlayerAttack2Right", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerAttack2Right", L"Animation\\Player\\Right\\SWING2.bmp");
		SetAnimationClipColorkey(L"PlayerAttack2Right", 255, 0, 255);
	}

	// Stab
	{
		AddAnimationClip(L"PlayerAttack3Left", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 2, 0, 0, 1, 2, 0.f, L"PlayerAttack3Left", L"Animation\\Player\\Left\\STAB.bmp");
		SetAnimationClipColorkey(L"PlayerAttack3Left", 255, 0, 255);

		AddAnimationClip(L"PlayerAttack3Right", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 2, 0, 0, 1, 2, 0.f, L"PlayerAttack3Right", L"Animation\\Player\\Right\\STAB.bmp");
		SetAnimationClipColorkey(L"PlayerAttack3Right", 255, 0, 255);
	}

	// Bow
	{
		AddAnimationClip(L"PlayerAttack4Left", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerAttack4Left", L"Animation\\Player\\Left\\BOW.bmp");
		SetAnimationClipColorkey(L"PlayerAttack4Left", 255, 0, 255);

		AddAnimationClip(L"PlayerAttack4Right", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 3, 0, 0, 1, 3, 0.f, L"PlayerAttack4Right", L"Animation\\Player\\Right\\BOW.bmp");
		SetAnimationClipColorkey(L"PlayerAttack4Right", 255, 0, 255);
	}

	 //Death 
	{
		vector<wstring> vecFileName;

		for (int i = 1; i <= 5; ++i) {
			wchar_t strFileName[MAX_PATH] = {};
			wsprintf(strFileName, L"PlayerDeath", L"Animation\\Player\\Frame\\%d.bmp", i);
			vecFileName.push_back(strFileName);
		}

		AddAnimationClip(L"PlayerDeath", AT_FRAME, AO_ONCE_RETURN,
			1.f, 1, 5, 0, 0, 1, 5, 0.f, L"PlayerDeath", vecFileName);
		SetAnimationClipColorkey(L"PlayerDeath", 255, 0, 255);
	}

	SAFE_RELEASE(pAni);

	m_iDir = 1;

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime); 

	if (KEYUP("Dead")) {
		Dead();
	}
	if (KEYUP("Debug")) {
		bool& Debug = GET_SINGLE(CCore)->GetInst()->bDebug;
		Debug = !Debug;
	}


	if (bRope == true) {
		if (KEYPRESS("Up")) {
			m_pAnimation->m_bAnimStop = false; 
			MoveY(-(m_fSpeed / 2), fDeltaTime);
		}
		else if (KEYPRESS("Down")) {
			m_pAnimation->m_bAnimStop = false;
			MoveY(m_fSpeed / 2, fDeltaTime);
		}
		else {
			m_pAnimation->m_bAnimStop = true; 
		}
	}

	if (KEYPRESS("MoveLeft") && bRope == false &&m_bAttack==false) {
		
		if (!m_bAttack&& bJump==false && bRope==false ) {
			m_pAnimation->ChangeClip(L"PlayerWalkLeft");
			m_pAnimation->SetDefaultClip(L"PlayerIdleLeft");
		}
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_iDir = -1;
	}
	if (KEYUP("MoveLeft")) {
		m_bMove = false; 
	}
	if (KEYPRESS("MoveRight") && bRope == false && m_bAttack==false)
		 {
		if (!m_bAttack && bJump==false && bRope==false ) {
			m_pAnimation->ChangeClip(L"PlayerWalkRight");
			m_pAnimation->SetDefaultClip(L"PlayerIdleRight");
		}
		MoveXFromSpeed(fDeltaTime, MD_FRONT);	
		m_iDir = 1;
	}
	if (KEYUP("MoveRight")) {
		m_bMove = false;
	}

	if (KEYDOWN("Attack")) {
		Attack();

		if(m_iDir==-1)
		m_pAnimation->ChangeClip(L"PlayerAttackLeft");

		if (m_iDir == 1)
		m_pAnimation->ChangeClip(L"PlayerAttackRight");
	}

	if (KEYDOWN("Attack2")) {
		Attack();

		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PlayerAttack2Left");

		if (m_iDir == 1)
			m_pAnimation->ChangeClip(L"PlayerAttack2Right");
	}

	if (KEYDOWN("Attack3")) {
		Attack();

		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PlayerAttack3Left");

		if (m_iDir == 1)
			m_pAnimation->ChangeClip(L"PlayerAttack3Right");
	}

	if (KEYUP("Attack4")) {
		Attack();

		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PlayerAttack4Left");

		if (m_iDir == 1)
			m_pAnimation->ChangeClip(L"PlayerAttack4Right");

		Fire();
	}

	if (KEYUP("Fire")) {
		Fire(); 
	}
	if (KEYDOWN("Skill1")) {
		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
	}
	if (KEYUP("Jump") ) {
		if (bRope == true) {
			return; 
		}
		if (bJump == false) {
			JumpDelta = 0.4f;
			MovePos.top = 275.f;
		}
		if (bJump == true) {
			
		}
		bJump = true;
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	if (bJump == true  &&
		m_bAttack==false && bRope==false  ) {

		if (m_iDir == -1){
			m_pAnimation->ChangeClip(L"PlayerJumpLeft");
			m_pAnimation->SetDefaultClip(L"PlayerJumpLeft");
		}
		else {
			m_pAnimation->ChangeClip(L"PlayerJumpRight");
			m_pAnimation->SetDefaultClip(L"PlayerJumpRight");
		}
	}

	if (m_bAttack == true && m_pAnimation->GetMotionEnd()) {
		m_bAttack = false;
	}

	if (m_bMove == false && m_bAttack == false &&
		bJump == false && bRope==false ) {
		if (m_iDir == -1) {
			m_pAnimation->SetDefaultClip(L"PlayerIdleLeft");
		}
		else {
			m_pAnimation->SetDefaultClip(L"PlayerIdleRight");
		}
		m_pAnimation->ReturnClip();
	};

	if (bRope == true ) {
	   m_pAnimation->ChangeClip(L"PlayerRope");
		m_pAnimation->SetDefaultClip(L"PlayerRope");
		
		// 로프애니메이션 재생
	}
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	 CMoveObj::LateUpdate(fDeltaTime);

	 if (HitDelta < 0) {
		 bHit = false; 
		 //HitDelta = 0;
	 }
	 HitDelta -= fDeltaTime;
	 return  0; 
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
};

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	HitRenderFlag = std::clamp<int>(HitRenderFlag + 1, 0, INT_MAX);
	if (bHit == true && HitRenderFlag % 4 == 0) {
		return; 
	}

	if (m_pTexture) {

		/*Rectangle(hDC, tPos.x, tPos.y, tPos.x + m_tSize.x, tPos.y + m_tSize.y);
		*/
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		POSITION tImagePos;

		if (m_pAnimation) {
			PANIMATIONCLIP pClip =
				m_pAnimation->GetCurrentClip();

			if (pClip->eType == AT_ATLAS) {
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		if (m_pTexture->bAlpha == true)
		{
			BLENDFUNCTION ftn;
			ftn.BlendOp = AC_SRC_OVER;
			ftn.BlendFlags = 0;
			ftn.SourceConstantAlpha = 255;
			ftn.AlphaFormat = AC_SRC_ALPHA;
			AlphaBlend(hDC, tPos.x, tPos.y, m_tSize.x,
				m_tSize.y,
				m_pTexture->GetDC(), tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, ftn);
		}
		else
		{
			if (m_pTexture->GetColorKeyEnable() == true) {
				TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x,
					m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y,
					m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
			}
			else {
				BitBlt(hDC, tPos.x, tPos.y,
					m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y,
					SRCCOPY);
			}
			/*BLENDFUNCTION ftn;
			ftn.BlendOp = AC_SRC_OVER;
			ftn.BlendFlags = 0;
			ftn.SourceConstantAlpha = 255;
			ftn.AlphaFormat = AC_SRC_OVER;

			AlphaBlend(hDC, tPos.x, tPos.y, m_tSize.x,
				m_tSize.y,
				m_pTexture->GetDC(), tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, ftn);*/
		}
	}

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}

	if (GET_SINGLE(CCore)->GetInst()->bDebug == true) {
		if (auto IsPlayer = dynamic_cast<CPlayer*>(this); IsPlayer != nullptr) {
			IsPlayer->DebugCollisionLinePrint(hDC);
		}
		else {
			DebugCollisionPrint(hDC);
		}
	}

#ifdef _DEBUG
		//DebugPrintHP(hDC, m_iHP);
		//CObj::DebugCollisionPrint(hDC);
#endif _DEBUG

}
void CPlayer::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
}
void CPlayer::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	
}
CPlayer* CPlayer::Clone()
{
	return new CPlayer{ *this };
}
void CPlayer::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj(L"Bullet",
		L"PlayerBullet",m_pScene->GetSceneType(),m_pLayer);

	POSITION tPos;
	
	/*auto [ColX,ColY]  = GetCollisionPos();*/

	if (m_iDir == -1) {
		tPos.x = GetCenter().x - pBullet->GetSize().x * (
			1.f - pBullet->GetPivot().x);
	}
	else if(m_iDir==1){
		tPos.x = GetCenter().x  + pBullet->GetSize().x * (
		pBullet->GetPivot().x);
	}
	tPos.y = GetCenter().y;
	pBullet->SetPos(tPos);

	if (auto DirSetUp = dynamic_cast<CMoveObj*>(pBullet); DirSetUp!=nullptr) {
		DirSetUp->SetDir(GetDir());
	}
	SAFE_RELEASE(pBullet); 
}
void CPlayer::Dead()&
{
	bDead = true; 
	
	if (GetDir() == -1) {
		m_pAnimation->ChangeClip(L"PlayerDeadLeft");
		m_pAnimation->SetDefaultClip(L"PlayerDeadLeft");
	}
	if (GetDir() == 1) {
		m_pAnimation->ChangeClip(L"PlayerDeadRight");
		m_pAnimation->SetDefaultClip(L"PlayerDeadRight");
	}
}
void CPlayer::Hit(CObj* const Target, float fDeltaTime)
{
	CMoveObj::Hit(Target, fDeltaTime);

	if (auto IsMonster = dynamic_cast<CMonster*>(Target);  
		IsMonster != nullptr&&HitDelta<0.f) {
		HitDelta = 2.f;
		bHit = true;
	};

	// 그라운드 충돌
	if (Target->GetTag() != L"StageColl") {
		bGround = false; 
	}
	else if (Target->GetTag() == L"StageColl") {
		bJump = false;
		bGround = true;
	}
};

