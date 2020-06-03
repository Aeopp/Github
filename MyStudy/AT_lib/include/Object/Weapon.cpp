#include "Weapon.h"
#include "Monster.h"
void Weapon::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CMoveObj::FirstHitEvent(Target, fDeltaTime);

	if (auto Monster = dynamic_cast<CMonster*>(Target); nullptr != Monster) {
		Monster->m_iHP -= Damage;
		if (Monster->m_iHP < 0) {
			Monster->Die();
		}
		else {
			Monster->CurrentState = EState::HIT;
			Monster->StateRemaining = 0.5f;
		}
	}
}
