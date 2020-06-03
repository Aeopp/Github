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

#include "../Core/Input.h"

#include "../../include/Object/UIPanel.h"
#include "../../include/Object/UIButton.h"
#include "../../Portal.h"
#include <tuple>
#include <utility>
#include "../../CHPBar.h"
#include "../../CDungeonScene2.h"
#include "../../DataTable.h"

CIngameScene::~CIngameScene() noexcept
{}

bool CIngameScene::Init()
{
	if (!CScene::Init())
		return false; 

	CLayer* pLayer = FindLayer(L"Default");

	auto* pPlayer = CObj::CreateObj<CPlayer>(L"Player", pLayer); 
	/*pPlayer->m_iHP = PlayerInfo::PlayerHP;
	pPlayer->Level = PlayerInfo::PlayerLevel;*/

	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f, 0.7f);
	GET_SINGLE(CCamera)->SetWorldResolution(2700, 1518);
	pPlayer->SetPos(1012,1274);

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
	
	

	if(StageFlag==false )
	pPortal->PortalEvent = []() {
		/*PlayerInfo::PlayerHP = pPlayer->m_iHP;
		PlayerInfo::PlayerLevel = pPlayer->Level;*/

		GET_SINGLE(CSceneManager)->CreateScene<CDungeonScecne>(SC_NEXT); 
	};
	else if (StageFlag == true)
	pPortal->PortalEvent = []() { 
		/*PlayerInfo::PlayerHP = pPlayer->m_iHP;
		PlayerInfo::PlayerLevel = pPlayer->Level;*/

		GET_SINGLE(CSceneManager)->CreateScene<CDungeonScene2>(SC_NEXT); 
	};

	StageFlag = !StageFlag;

	SAFE_RELEASE(pPortal);

	CLayer* pUILayer = FindLayer(L"UI");
	CurrentUIMinimap = CObj::CreateObj<CUIPanel>(L"pMinimapUI", pUILayer);

	CurrentUIMinimap->SetSize(195, 120);
	CurrentUIMinimap->SetTexture(L"MinimapUI",
		L"HappyMinimap.bmp");

	pPlayer->HPBarSpawn({ 0,(float)GET_SINGLE(CCore)->GetResolution().iH - 71 },
		{ 570,71 }, { L"Bar1",L"Bar2" }, { L"BAR1.bmp",L"BAR2.bmp" }, pUILayer);

	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(CurrentUIMinimap);
	

	return true;
}

int CIngameScene::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	if (KEYDOWN("Stage1")) {
		StageFlag = true; 
	}
	if (KEYDOWN("Stage2")) {
		StageFlag = false; 
	}
	return 0;
}


void CIngameScene::EndButtonCallback(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}


