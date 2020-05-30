#include "Dungeon.h"
#include "include/Resources/Texture.h"
#include "include/CCore.h"
#include "include/Core/Camera.h"
#include "include/../DataTable.h"

bool CDungeon::Init()
{
	SetPos(0.f, 0.f);
	SetSize(2250,1375);
	SetPivot(0.f, 0.f);

	SetTexture(L"Dungeon.bmp", L"Map\\Dungeon.bmp");

	return true;
}

void CDungeon::Render(HDC hDC, float fDeltaTime)
{
	// CStaticObj::Render(hDC, fDeltaTime);
	CStage::Render(hDC, fDeltaTime);
}


CDungeon* CDungeon::Clone()
{
	return new CDungeon(*this);
}
