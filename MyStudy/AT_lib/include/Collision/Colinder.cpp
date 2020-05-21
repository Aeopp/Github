#include "Colinder.h"
#include "../Object/Obj.h"
CColinder::CColinder()
{
}

CColinder::~CColinder()noexcept
{
}

CColinder::CColinder(const CColinder& coll) {
	*this = coll;
}
bool CColinder::Init()
{
	return true;
}

void CColinder::Input(float fDeltaTime)
{
}

int CColinder::Update(float fDeltaTime)
{
	return 0;
}

int CColinder::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CColinder::Collision(float fDeltaTime)
{
}

void CColinder::Render(HDC hDC, float fDeltaTime)
{
}

CColinder* CColinder::Clone()
{
	return nullptr;
}
