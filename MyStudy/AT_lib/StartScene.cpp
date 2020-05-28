#include "StartScene.h"
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

CStartScene::CStartScene()
{
};

CStartScene::~CStartScene()
{
}
void CStartScene::Render(HDC hDC, float fDeltaTime)
{
    CScene::Render(hDC, fDeltaTime);
    //
    //for (auto& UI: UIs) {
    //    // 사용자가 버튼을 눌렀다면
    //    UI->m_pAnimation->ChangeClip(L"StartButton");
    //    UI->m_pAnimation->SetDefaultClip(L"StartButton");
    //}
};

bool CStartScene::Init()
{
    if (!CScene::Init())
        return false; 

    CLayer* pLayer = FindLayer(L"UI");

	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>(L"BackPanel", pLayer);

    pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
    pBackPanel->SetTexture(L"StartBack",
     L"StartBack.bmp");

    SAFE_RELEASE(pBackPanel);


    CUIButton* pEndBtn = CObj::CreateObj<CUIButton>(L"EndButton", pLayer);

    pEndBtn->SetPos(GETRESOLUTION.iW / 2 -
        350, GETRESOLUTION.iH / 2 - 100);
    pEndBtn->SetSize(300, 200);
    pEndBtn->SetTexture(L"EndButton",
        L"StartButton.bmp");
    pEndBtn->SetColorKey(255, 0, 255);
    pEndBtn->bBorder = false;


    pEndBtn->SetCallback(this,
        &CStartScene::StartButtonCallback);


    SAFE_RELEASE(pEndBtn);


    /*    CColliderRect* pRC = (CColliderRect*)pStartBtn->GetCollider(L"ButtonBody");

        POSITION tPos = pStartBtn->GetPos();
        pRC->SetRect(tPos.x,tPos.y,tPos.x+200,
            tPos.y+100);*/


        //CUIButton* pEndBtn= CObj::CreateObj<CUIButton>(L"EndButton", pLayer);

        //pEndBtn->SetPos(GETRESOLUTION.iW / 2 -
        //    100, GETRESOLUTION.iH / 2 +20);
        //pEndBtn->SetSize(174, 140);
        //pEndBtn->SetTexture(L"EndButton",
        //    L"StartButton.bmp");
        //pStartBtn->SetColorKey(255, 0, 255);


      /*   pRC = (CColliderRect*)pEndBtn->GetCollider(L"ButtonBody");

         tPos = pEndBtn->GetPos();
        pRC->SetRect(tPos.x, tPos.y, tPos.x + 200,
            tPos.y + 100);

        SAFE_RELEASE(pRC);*/

        //SAFE_RELEASE(pEndBtn);

        return true;
}

void CStartScene::StartButtonCallback(float fTime)
{
    GET_SINGLE(CSceneManager)->CreateScene<CIngameScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fTime)
{
    GET_SINGLE(CCore)->DestroyGame();
}
