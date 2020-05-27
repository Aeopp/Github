#include "Stage.h"
#include "../Resources/Texture.h"
#include "../CCore.h"
#include "../Core/Camera.h"
#include "../../DataTable.h"
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
	SetSize(Stage::SizeWidth,
		Stage::SizeHeight);
	SetPivot(0.f, 0.f);

	SetTexture(Stage::Key.c_str(), Stage::Filename.c_str());

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
		POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

		BitBlt(hDC, tPos.x, tPos.y,
			GETRESOLUTION.iW, GETRESOLUTION.iH, m_pTexture->GetDC(), tCamPos.x, tCamPos.y,
			SRCCOPY);
	}
}

CStaticObj* CStage::Clone()
{
	return new CStage(*this);
}
