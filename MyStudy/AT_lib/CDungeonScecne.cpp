#pragma once
#include "CDungeonScecne.h"
#include "include/Object/UIButton.h"
#include "include/Object/UIPanel.h"
#include "include/Core/Camera.h"
#include "include/Scene/Layer.h"
#include "include/../Pixel.h" 
#include "include/CCore.h"
#include "include/Collision/ColinderRect.h"
#include "CAnimation.h"
#include "include/Scene/CSceneManager.h"
#include "include/Scene/CIngameScene.h"
#include "StartScene.h"
#include "include/Object/Player.h"
#include "include/Object/Mushroom.h"
#include "include/Object/Bullet.h"
#include "Ground.h"
#include "Rope.h"
#include "include/Object/Stage.h"
#include "Portal.h"
#include "Dungeon.h"
#include "include/Object/Slime.h"
#include "DamagePont.h"
#include "CHPBar.h"

bool CDungeonScecne::Init()
{
	if (!CScene::Init())
		return false;
	CLayer* pLayer = FindLayer(L"Default");
	
	auto* pPlayer = CObj::CreateObj<CPlayer>(L"Player", pLayer);
	pPlayer->SetWeapon(pLayer);

	/*MonstersSpawn<CSlime>(pLayer, L"Slime", { {421,593},{552,593} }, { 280,680 });
	MonstersSpawn<CSlime>(pLayer, L"Slime", { {1840,501},{2004,501},{2103,501} }, { 1739,2221 });*/

	MonstersSpawn<CPig>(pLayer, L"Pig", { {1040,472},{1236,472}
		,{938,197},{1298,197},{1393,197} }, { 837,1440 });

	/*MonstersSpawn<CPig>(pLayer, L"Pig", { {1040,472},{1236,472}
		,{938,197},{1298,197},{1393,197} }, { 837,1440 });*/

	//MonstersSpawn<CMushroom>(pLayer, L"Mushroom", { {1057, 900}, { 1256,900 }, { 1400,900 } }, { 838,1443 });
	//
	//MonstersSpawn<CMushroom>(pLayer, L"Mushroom", {  {176, 1052}, { 399,1052 }
	//	, { 838,1052 }}, { 40,2163 });

	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f, 0.3f);
	GET_SINGLE(CCamera)->SetWorldResolution(2250, 1375);

	pPlayer->SetPos(1600, 800);

	CBullet* pBullet = CScene::CreateProtoType<CBullet>(L"Bullet",
		m_eSceneType);
	pBullet->SetSize(369.f, 116.f);
	pBullet->SetSpeed(1000.f);
	SAFE_RELEASE(pBullet);

	CLayer* pStageLayer = FindLayer(L"Stage");

	Portal* pPortal = CObj::CreateObj<Portal>(L"Portal2", pStageLayer);
	pPortal->SetPos(1152, 170);
	pPortal->PortalEvent = []() {GET_SINGLE(CSceneManager)->CreateScene<CStartScene>(SC_NEXT); };
	SAFE_RELEASE(pPortal);

	CDungeon* pStage = CObj::CreateObj<CDungeon>(L"Stage", pStageLayer);
	pStage->SetGroundHeight(1120);
	GET_SINGLE(CSceneManager)->CurrentStageGroundHeight = 1120;

	CGround* Ground = CObj::CreateObj<CGround>(L"StageColl", pStageLayer);
	Ground->SetPos(0, 1110);
	Ground->SetSize(POSITION{ 2250,200});

	CRope* Rope = CObj::CreateObj<CRope>(L"StageColl", pStageLayer);
	Rope->SetPos(548, 840);
	Rope->SetSize(POSITION{ 10,1041- 840 });
	
	GroundsSetUps(EMapObjType::GROUND,pStageLayer, 
		{ {652,1089,725}, {740,1030,815}, {831,970,1504}, {1517,1031,1598}, {1605,1089,1689},
				   {1548 ,909, 1686},
	{ 1732 ,848 ,1866 },
		{1730  ,609, 2226},
		{650   ,910, 788  },
		{1639  ,550, 1777},
		{1550  ,490, 1688},
		{1821  ,369, 2227},
		{831   ,249, 1503 },
		{380   ,849, 606  },
		{290   ,670,  692 },
		{651   ,610, 785  },
		{651   ,489, 785  },
		{471   ,429, 602  },
		{20    ,369, 425},
		{838 ,548 ,1500} });

	GroundsSetUps(EMapObjType::ROPE, pStageLayer,
		{ {632,670,850} ,{1772,610,798} ,{282,372,614} ,{1176,250,541} ,{2023,372,557}  });

	SAFE_RELEASE(pStage);
	SAFE_RELEASE(Ground);

	CLayer* pUILayer = FindLayer(L"UI");

	auto* CurrentDamage = CObj::CreateObj<DamagePont>(L"DamagePont", pUILayer);
	GET_SINGLE(CSceneManager)->CurrentDamagePont = CurrentDamage;

	CurrentUIMinimap = CObj::CreateObj<CUIPanel>(L"pMinimapUI", pUILayer);
	CurrentUIMinimap->SetSize(160, 150);
	CurrentUIMinimap->SetTexture(L"MinimapUI2",
		L"Minimap.bmp");

	pPlayer->HPBarSpawn({ 0,(float)GET_SINGLE(CCore)->GetResolution().iH - 71 },
		{ 570,71 }, { L"Bar1",L"Bar2" }, { L"BAR1.bmp",L"BAR2.bmp" }, pUILayer);

	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(CurrentUIMinimap);
	
    return true;
}

void CDungeonScecne::StartButtonCallback(float fTime)
{
    GET_SINGLE(CSceneManager)->CreateScene<CStartScene>(SC_NEXT);
}

void CDungeonScecne::EndButtonCallback(float fTime)
{
    GET_SINGLE(CCore)->DestroyGame();
}
