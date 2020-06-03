#include "Monster.h"
#include "../Core/Timer.h"
#include "../../CMath.h"
void CMonster::FirstHitEvent(CObj*const  Target, float fDeltaTime)
{
	CMoveObj::FirstHitEvent(Target, fDeltaTime);
	if (Target->GetTag() == L"Player") {
		Dead();
		//MessageBox(WINDOWHANDLE, L"공격!", L"공격!", NULL); 
	};
}

void CMonster::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	
		CMoveObj::ReleaseHitEvent(Target, fDeltaTime);
	
}

int CMonster::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	RandomState(fDeltaTime);
	AnimationCalc();

	if (CurrentState == EState::WALK) {
		MoveXFromSpeed(fDeltaTime, static_cast<MOVE_DIR>(m_iDir));
	}

	if (CurrentState == EState::JUMP) {
		if (bJump == false) {
			JumpDelta = 0.4f;
			MovePos.top = 150.f;
		};
		bJump = true;
	};
	auto [left, right] = MonsterXRange;

	m_tPos.x = std::clamp<float>(m_tPos.x,left,right);
	
	return 0;
}

void CMonster::Hit(CObj* const Target, float fDeltaTime)
{
		CMoveObj::ReleaseHitEvent(Target, fDeltaTime);
}

int CMonster::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;  
}

 void CMonster::RandomState(float fDeltaTime)&
{
	StateRemaining -= fDeltaTime;

	if (StateRemaining < 0.f) {
		CurrentState = static_cast<EState>(CMath::GetRandomNumber(0, 2));
		if (CurrentState == EState::JUMP) {
			StateRemaining = 0.3f;
		}
		else
			StateRemaining = CMath::GetRandomNumber(2, 4);

		m_iDir = CMath::GetRandomNumber(-1, 1);
	};
}

void CMonster::Dead()&
{
	CurrentState = EState::DIE;
	StateRemaining = 0.7f;

	GET_SINGLE(CTimer)->PushTimer(0.7f, ETimerState::ONCE, [&](float) {
		bDead = true; 
		bCollision = false; 
		GET_SINGLE(CTimer)->PushTimer(15.f, ETimerState::ONCE, [&](float) {
			bDead = false;
			bCollision = true; 
			});
		});
};

