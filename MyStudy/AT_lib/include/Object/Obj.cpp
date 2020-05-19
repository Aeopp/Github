#include "Obj.h"

CObj::CObj() {};

CObj::~CObj()
{
	SAFE_DELETE(m_pScene);
	SAFE_DELETE(m_pLayer); 
}
CObj::CObj(const CObj & Obj)
{
	*this = Obj;
}



void CObj::Input(float fDeltaTime)
{

}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
}
