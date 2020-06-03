#include "Monster.h"
#include "../CCore.h"
#include "../Resources/Texture.h"
#include "../Collision/ColinderRect.h"
#include "../Scene/CScene.h"
#include "../Core/Input.h"
#include <cassert>
#include "../../CAnimation.h"
#include "../../CMath.h"
CMonster::CMonster(const CMonster& Monster)
{

}

bool CMonster::Init()
{
	// 몬스터 스폰 위치 지정
	SetPos(0.f, 0);
	SetSize(80, 70.f);
	SetSpeed(200.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetCorrectionRenderToCollision(RECTANGLE{0,0,0,0});

	SetTexture(L"Slime", L"Animation/Monster/Slime/HIT.bmp");
	SetColorKey(255, 0, 255);

	//SetCorrectionRenderToCollision(RECTANGLE{110,54,151,128});

	// HP 지정
	m_iHP = 1000;
	SetPhysics(true);
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation(L"SlimeAnimation");

	// TODO :: ANIMATION Field
	// Idle 
	{
		AddAnimationClip(L"SlimeIdleright", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"SlimeIdleright", L"Animation\\Monster\\Right\\IDLE.bmp");
		SetAnimationClipColorkey(L"SlimeIdleright", 255, 0, 255);

		AddAnimationClip(L"SlimeIdleleft", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"SlimeIdleleft", L"Animation\\Monster\\Left\\IDLE.bmp");
		SetAnimationClipColorkey(L"SlimeIdleleft", 255, 0, 255);
	}
	//DIE
	{
		AddAnimationClip(L"SlimeDieleft", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 4, 0, 0, 1, 4, 0.f, L"SlimeDieleft", L"Animation\\Monster\\Left\\DIE.bmp");
		SetAnimationClipColorkey(L"SlimeDieleft", 255, 0, 255);
		
		AddAnimationClip(L"SlimeDieRight", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 4, 0, 0, 1, 4, 0.f, L"SlimeDieRight", L"Animation\\Monster\\Right\\DIE.bmp");
		SetAnimationClipColorkey(L"SlimeDieRight", 255, 0, 255);
	}
	// HIT 
	{
		AddAnimationClip(L"SlimeHitleft", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeHitleft", L"Animation\\Monster\\Left\\HIT.bmp");
		SetAnimationClipColorkey(L"SlimeHitleft", 255, 0, 255);

		AddAnimationClip(L"SlimeHitright", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeHitright", L"Animation\\Monster\\Right\\HIT.bmp");
		SetAnimationClipColorkey(L"SlimeHitright", 255, 0, 255);
	}

	//JUMP
	{
		AddAnimationClip(L"SlimeJumpleft", AT_ATLAS, AO_LOOP,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeJumpleft", L"Animation\\Monster\\Left\\JUMP.bmp");
		SetAnimationClipColorkey(L"SlimeJumpleft", 255, 0, 255);

		AddAnimationClip(L"SlimeJumpright", AT_ATLAS, AO_LOOP,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeJumpright", L"Animation\\Monster\\Right\\JUMP.bmp");
		SetAnimationClipColorkey(L"SlimeJumpright", 255, 0, 255);

	}

	// Walk
	{
		AddAnimationClip(L"SlimeWalkleft", AT_ATLAS, AO_LOOP,
			0.6f, 1, 7, 0, 0, 1, 7, 0.f, L"SlimeWalkleft", L"Animation\\Monster\\Left\\WALK.bmp");
		SetAnimationClipColorkey(L"SlimeWalkleft", 255, 0, 255);

		AddAnimationClip(L"SlimeWalkright", AT_ATLAS, AO_LOOP,
			0.6f, 1, 7, 0, 0, 1, 7, 0.f, L"SlimeWalkright", L"Animation\\Monster\\Right\\WALK.bmp");
		SetAnimationClipColorkey(L"SlimeWalkright", 255, 0, 255);
	}

	SAFE_RELEASE(pAni);

	m_iDir = 1;


	return true;
};

CMonster* CMonster::Clone()
{
	return new CMonster{ *this } ;
}

void CMonster::RandomState(float fDeltaTime)&
{
	StateRemaining -= fDeltaTime;

	if (CurrentState == EState::HIT || CurrentState == EState::DIE) {
		return;
	};

	if (StateRemaining < 0.f) {
		CurrentState=static_cast<EState>(CMath::GetRandomNumber(0, 2));
	}
}

CMonster::CMonster() : CMoveObj()
{
}

CMonster::~CMonster() noexcept
{
}

CMonster::CMonster(const CMonster& Monster) :
	CMoveObj(Monster) {
	*this = Monster;
};

void CMonster::Attack()&
{
	m_bAttack = true;
};

void CMonster::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);
}

int CMonster::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	if (bJump == true) {
		if (m_iDir == -1) {
			m_pAnimation->ChangeClip(L"SlimeJumpleft");
			m_pAnimation->SetDefaultClip(L"SlimeJumpleft");
		}
		else {
			m_pAnimation->ChangeClip(L"SlimeJumpright");
			m_pAnimation->SetDefaultClip(L"SlimeJumpright");
		}
	}

	if (m_bAttack == true && m_pAnimation->GetMotionEnd()) {
		m_bAttack = false;
	}

	if (m_bMove == false && m_bAttack == false &&
		bJump == false && bRope == false) {
		if (m_iDir == -1) {
			m_pAnimation->SetDefaultClip(L"SlimeIdleleft");
		}
		else {
			m_pAnimation->SetDefaultClip(L"SlimeIdleright");
		}
		m_pAnimation->ReturnClip();
	};
	if (bDead == true) {
		Dead();
	};

	if (  왼쪽으로 걷는 상태 && m_bAttack == false) {

		if (!m_bAttack && bJump == false) {
			m_pAnimation->ChangeClip(L"SlimeWalkleft");
			m_pAnimation->SetDefaultClip(L"SlimeWalkleft");
		}
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_iDir = -1;
	}
	if (왼쪽으로 걷는 상태가 끝나면 ) {
		m_bMove = false;
	}
	if (오른쪽으로 걷는 상태 &&  m_bAttack == false)
	{
		if (!m_bAttack && bJump == false) {
			m_pAnimation->ChangeClip(L"SlimeWalkright");
			m_pAnimation->SetDefaultClip(L"SlimeWalkright");
		}
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_iDir = 1;
	}
	if (오른쪽으로 걷는 상태가 끝나면) {
		m_bMove = false;
	}

	if (점프 상태) {
		if (bJump == false) {
			JumpDelta = 0.4f;
			MovePos.top = 275.f;
		};

		bJump = true;
	};

	return 0;
}

int CMonster::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);

	return  0;
}

void CMonster::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
};

void CMonster::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

#ifdef _DEBUG
	//DebugPrintHP(hDC, m_iHP);
	//CObj::DebugCollisionPrint(hDC);
#endif _DEBUG

}
void CMonster::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
}
void CMonster::FirstHitEvent(CObj* const Target, float fDeltaTime)
{

};

void CMonster::Dead()&
{
	bDead = true;

	if (GetDir() == -1) {
		m_pAnimation->ChangeClip(L"SlimeDieleft");
		m_pAnimation->SetDefaultClip(L"SlimeDieleft");
	}
	if (GetDir() == 1) {
		m_pAnimation->ChangeClip(L"SlimeDieright");
		m_pAnimation->SetDefaultClip(L"SlimeDieright");
	}
}
void CMonster::Hit(CObj* const Target, float fDeltaTime)
{
	CObj::Hit(Target, fDeltaTime);

	if (Target->GetTag() == L"Player") {
		MessageBox(WINDOWHANDLE, L"공격!", L"공격!", NULL); 
	};

	if (Target->GetTag() != L"StageColl") {
		bGround = false;
	}
	else if (Target->GetTag() == L"StageColl") {
		bJump = false;
		bGround = true;
	}
};

