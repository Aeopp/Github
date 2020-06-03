#include "CIngameScene.h"
#include "../Object/Player.h"
#include "../Object/Mushroom.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
#include "../Core/Camera.h"
#include "Layer.h"
#include "../../Pixel.h"

#include "../Scene/CSceneManager.h"
#include "../CCore.h"
#include "../../Dungeon.h"
#include "../../CDungeonScecne.h"
#include "../../include/Object/UIPanel.h"
#include "../../include/Object/UIButton.h"
#include "../../Portal.h"
#include <tuple>
#include <utility>
#include "../../CHPBar.h"

CIngameScene::~CIngameScene() noexcept
{}

bool CIngameScene::Init()
{
	if (!CScene::Init())
		return false; 

	CLayer* pLayer = FindLayer(L"Default");

	auto* pPlayer = CObj::CreateObj<CPlayer>(L"Player", pLayer); 
	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f, 0.7f);
	GET_SINGLE(CCamera)->SetWorldResolution(2700, 1518);
	pPlayer->SetPos(1012,1274);

	CBullet* pBullet = CScene::CreateProtoType<CBullet>(L"Bullet",
		m_eSceneType);
	pBullet->SetSize(369.f, 116.f);
	pBullet->SetSpeed(1000.f);
	SAFE_RELEASE(pBullet);

	CLayer* pStageLayer = FindLayer(L"Stage");

	CStage* pStage = CObj::CreateObj<CStage>(L"Stage", pStageLayer);
	pStage->SetStageInfo(2250, 1375, L"Dungeon", L"Map\\Dungeon.bmp");
	pStage->SetGroundHeight(1400);
	GET_SINGLE(CSceneManager)->CurrentStageGroundHeight = 1400;

	CGround* Ground = CObj::CreateObj<CGround>(L"StageColl", pStageLayer);
	Ground->SetPos(0,1400);
	Ground->SetSize(POSITION{ 2700,200 });

	SAFE_RELEASE(pStage); 
	SAFE_RELEASE(Ground);

	Portal* pPortal = CObj::CreateObj<Portal>(L"Portal", pStageLayer);

	pPortal->SetPos(427, 1346);
	/*pPortal->SetTexture(L"Portal",
		L"Portal.bmp");*/
	pPortal->PortalEvent = []() { GET_SINGLE(CSceneManager)->CreateScene<CDungeonScecne>(SC_NEXT); };

	SAFE_RELEASE(pPortal);

	CLayer* pUILayer = FindLayer(L"UI");
	CurrentUIMinimap = CObj::CreateObj<CUIPanel>(L"pMinimapUI", pUILayer);

	CurrentUIMinimap->SetSize(195, 120);
	CurrentUIMinimap->SetTexture(L"MinimapUI",
		L"HappyMinimap.bmp");

	pPlayer->HPBarSpawn({ 0,(float)GET_SINGLE(CCore)->GetResolution().iH - 71 },
		{ 570,71 }, { L"Bar1",L"Bar2" }, { L"BAR1.bmp",L"BAR2.bmp" }, pUILayer);

	//auto [HPBackGround,HPBar] = pPlayer->CurrentHPBar;

	//HPBackGround = CObj::CreateObj<CHPBar>(L"Bar1", pUILayer);
	//HPBackGround->SetPos(0,GET_SINGLE(CCore)->GetResolution().iH-71);
	//HPBackGround->SetSize(570, 71);
	//HPBackGround->SetTexture(L"Bar1",L"BAR1.bmp");
	//HPBackGround->SetColorKey(255, 0, 255);
	//HPBackGround->bBorder = false;

	//HPBar = CObj::CreateObj<CHPBar>(L"Bar2", pUILayer);
	//HPBar->SetPos(0, GET_SINGLE(CCore)->GetResolution().iH - 71);
	//HPBar->SetSize(570, 71);
	//HPBar->SetTexture(L"Bar2", L"BAR2.bmp");
	//HPBar->SetColorKey(255, 0, 255);
	//HPBar->bBorder = false;

	//pPlayer->CurrentHPBar.first = HPBackGround;
	//pPlayer->CurrentHPBar.second= HPBar;



	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(CurrentUIMinimap);
	

	return true;
}


void CIngameScene::EndButtonCallback(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}


