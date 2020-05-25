#include "CCore.h"
#include "Scene/CSceneManager.h"
#include "Core/Timer.h"
#include "Resources/ResourcesManager.h"
#include "Resources/Texture.h"
#include "Core\Camera.h"
#include "Core\Input.h"
#include "Collision\CollisionManager.h"
#include "Object/Mushroom.h"
#include "Object/Stage.h"
void CCore::DestroyInst() {
	SAFE_DELETE(m_pInst);
	DESTROY_SINGLE(CSceneManager);
//	DESTROY_SINGLE(CCollisionManager);
	DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(CCamera);
	DESTROY_SINGLE(CResourcesManager); 
	DESTROY_SINGLE(CPathManager);
	DESTROY_SINGLE(CTimer);

	ReleaseDC(m_hWnd, m_hDC);
}

bool CCore::Init(HINSTANCE hInst)
{
	m_hInst = hInst;
	MyRegisterClass(); 

	m_tRS.iW = 1280;
	m_tRS.iH = 720;
	Create();

	m_hDC = GetDC(m_hWnd);

	if (!GET_SINGLE(CTimer)->Init()){
		return false;
	}
	if (!GET_SINGLE(CPathManager)->Init()){
		return false;
	}
	if (!GET_SINGLE(CResourcesManager)->Init(hInst,m_hDC)) {
		return false;
	}
	if (!GET_SINGLE(CInput)->Init(m_hWnd)) {
		return false;
	}
	if (!GET_SINGLE(CCamera)->Init(POSITION{ 0.f, 0.f },
		m_tRS, RESOLUTION(5830.f, 3279.f))){
		return false; 
	}
	if (!GET_SINGLE(CSceneManager)->Init()) {
		return false; 
	}
	return true ;
}

int CCore::Run()
{
	MSG msg;
	while (m_bLoop) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else {
			Logic();
		}
	}
	return (int)msg.wParam;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		//TODO... 

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam); }
	break;
	}
	return 0;
}

void CCore::Logic()
{
	GET_SINGLE(CTimer)->Update();

	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

	Input(fDeltaTime); 
	Update(fDeltaTime);
	LateUpdate(fDeltaTime);
	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
	GET_SINGLE(CInput)->Update(fDeltaTime);
	GET_SINGLE(CSceneManager)->Input(fDeltaTime);
	GET_SINGLE(CCamera)->Input(fDeltaTime); 
}

int CCore::Update(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->Update(fDeltaTime);
	GET_SINGLE(CCamera)->Update(m_hDC,fDeltaTime);
	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);

	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	// TODO :: 여기서 충돌 검사하기전에 테이블 세팅 보장 해줘야함 !!!!!!!!!!!!
	GET_SINGLE(CSceneManager)->Collision(fDeltaTime);

	if (CObj::m_ObjList.size() < 2) {
		return; 
	}

	for (auto Outer = std::begin(CObj::m_ObjList);
		Outer != std::end(CObj::m_ObjList);++Outer) {
		auto Inner = Outer;
		std::advance(Inner, 1);

		for (Inner; Inner != std::end(CObj::m_ObjList); ++Inner) {
			auto LhsRect = (*Inner)->GetCollisionRect();
			auto RhsRect = (*Outer)->GetCollisionRect();
			if (true == CollisionRectToRect(LhsRect, RhsRect)) {
				auto LhsTag = (*Inner)->GetTag();
				auto RhsTag = (*Outer)->GetTag();

				if (LhsTag == L"Stage" || RhsTag == L"Stage")continue;

				(*Inner)->Hit(*Outer, fDeltaTime);
				(*Outer)->Hit(*Inner, fDeltaTime);
				//MessageBox(NULL, LhsTag.c_str(), RhsTag.c_str(),MB_OK);
			}
			else {
				/*auto InnerPair = (*Inner)->FindHitList(*Outer);

				if (InnerPair.second == ECOLLISION_STATE::First ||
					InnerPair.second == ECOLLISION_STATE::Keep) {
					
					auto hit_list = InnerPair.first->GetHitList();
					auto is_find = std::find(std::begin(hit_list), 
						std::end(hit_list),
						[Outer](pair<CObj*,ECOLLISION_STATE> pair) {if (  pair.first == *Outer)
						return true;  });
					if (is_find != std::end(hit_list)) {
						is_find->second = ECOLLISION_STATE::Release;
					}*/
					
				}
				/*else {*/
					/*auto hit_list = InnerPair.first->GetHitList();
					auto is_find = std::find(std::begin(hit_list), std::end(hit_list),
						[Outer](pair<CObj*,ECOLLISION_STATE> pair) {if (pair.first == *Outer)
						return true;  });
					if (is_find != std::end(hit_list)) {
						is_find->second = ECOLLISION_STATE::Nothing;
					}*/
				/*}*/

			/*	auto OuterPair = (*Outer)->FindHitList(*Inner);

				if (OuterPair.second == ECOLLISION_STATE::First ||
					OuterPair.second == ECOLLISION_STATE::Keep) {

					OuterPair.first->SetHitList(*Inner, ECOLLISION_STATE::Release);
				}
				else{
					OuterPair.first->SetHitList(*Inner, ECOLLISION_STATE::Nothing);
				}*/
			/*}*/
		}
	}

	//for (CObj* element : CObj::m_ObjList) {

	//	//if (CMushroom* Mush = dynamic_cast<CMushroom*>(element);
	//	//	Mush != nullptr)
	//	//{
	//	//	Mush->GetCollisionPos();

	//	//	/*Rectangle(pBackBuffer->GetDC(), tPos.x, tPos.y,
	//	//		tPos.x + Size.x, tPos.y + Size.y);*/
	//	//}
	//}


	// 버그버그버그
	//GET_SINGLE(CCollisionManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
	CTexture* pBackBuffer = GET_SINGLE(CResourcesManager)->GetBackBuffer();

	Rectangle(pBackBuffer->GetDC(), 0, 0, 1280, 720);
	
	GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDC(),fDeltaTime);

	

	BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, pBackBuffer->GetDC(),
		0, 0, SRCCOPY);

	SAFE_RELEASE(pBackBuffer); 
}

ATOM CCore::MyRegisterClass()
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MapleStory"; 
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	
	return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
	m_hWnd = CreateWindowW(L"MapleStory", L"MapleStory", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr,
		m_hInst, nullptr);

		if (!m_hWnd) {
			return FALSE;
		}

		RECT rc = { 0,0,m_tRS.iW,m_tRS.iH};
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100,
			rc.right - rc.left,
			rc.bottom - rc.top,
			SWP_NOMOVE | SWP_NOZORDER);

		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);

	return 0;
}

CCore::CCore()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(229);
};

CCore::~CCore() noexcept
{
	/*DESTROY_SINGLE(CCore);
	DESTROY_SINGLE(CTimer);*/
	//DESTROY_SINGLE(CTimer);
}

