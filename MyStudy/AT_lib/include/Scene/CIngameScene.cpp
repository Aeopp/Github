#include "CIngameScene.h"
#include "../Object/Player.h"
#include "../Object/Mushroom.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
#include "../Core/Camera.h"
#include "Layer.h"
#include "../../Pixel.h"
#include "../../Ground.h"

CIngameScene::~CIngameScene() noexcept
{}

bool CIngameScene::Init()
{
	if (!CScene::Init())
		return false; 

	CLayer* pLayer = FindLayer(L"Default");

	auto* pPlayer = CObj::CreateObj<CPlayer>(L"Player", pLayer); 
	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f, 0.3f);

	SAFE_RELEASE(pPlayer);

	auto* pMushroom = CObj::CreateObj<CMushroom>
		(L"Mushroom", pLayer); 
	SAFE_RELEASE(pMushroom);

	CBullet* pBullet = CScene::CreateProtoType<CBullet>(L"Bullet");
	pBullet->SetSize(369.f, 116.f);
	pBullet->SetSpeed(1000.f);
	SAFE_RELEASE(pBullet);

	CLayer* pStageLayer = FindLayer(L"Stage");

	CStage* pStage = CObj::CreateObj<CStage>(L"Stage", pStageLayer);

	CGround* Ground = CObj::CreateObj<CGround>(L"StageColl", pStageLayer);
	Ground->SetPos(0,1400);
	Ground->SetSize(POSITION{ 2700,100 });

	//CPixel* pPixel = CObj::CreateObj<CPixel>(L"StageColl", pStageLayer);
	//pPixel->SetPixelInfo("Happy.bmp");
	//SAFE_RELEASE(pPixel);

	SAFE_RELEASE(pStage); 

	return true;
}
