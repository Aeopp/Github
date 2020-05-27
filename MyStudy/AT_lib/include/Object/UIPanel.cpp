#include "UIPanel.h"

CUIPanel::CUIPanel()
{
}

CUIPanel::CUIPanel(const CUIPanel& ui):
	CUI(ui)
{
}

CUIPanel::~CUIPanel()
{
}

bool CUIPanel::Init()
{
	return true;
}

void CUIPanel::Input(float fDeltaTime)
{
}

int CUIPanel::Update(float fDeltaTime)
{
	return 0;
}

int CUIPanel::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CUIPanel::Collision(float fDeltaTime)
{
}

void CUIPanel::Hit(CObj* const Target, float fDeltaTime)
{
}

void CUIPanel::Render(HDC hDC, float fDeltaTime)
{
}

CUIPanel* CUIPanel::Clone()
{
	return new CUIPanel{ *this };
}
