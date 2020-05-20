#include "Stage.h"
#include "../Resources/Texture.h"
#include "../CCore.h"
CStage::CStage():
	CStaticObj()
{
}

CStage::~CStage() noexcept
{
}

CStage::CStage(const CStage& Obj):
	CStaticObj(Obj)
{
}

bool CStage::Init()
{
	SetPos(0.f, 0.f);
	SetSize(2700.f,673.f);
	SetPivot(0.f, 0.f);

	SetTexture(L"Stage1", L"Happy.bmp");

	return true;
}

void CStage::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime)
{
	return CStaticObj::Update(fDeltaTime);
}

int CStage::LateUpdate(float fDeltaTime)
{
	return CStaticObj::LateUpdate(fDeltaTime);
}

void CStage::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

void CStage::Render(HDC hDC, float fDeltaTime)
{
	// CStaticObj::Render(hDC, fDeltaTime);

	if (m_pTexture) {
		POSITION tPos = m_tPos - m_tSize * m_tPivot;

		BitBlt(hDC, tPos.x, tPos.y,
			GETRESOLUTION.iW, GETRESOLUTION.iH, m_pTexture->GetDC(), 0, 0,
			SRCCOPY);
	}
}

CStaticObj* CStage::Clone()
{
	return new CStage(*this);
}
