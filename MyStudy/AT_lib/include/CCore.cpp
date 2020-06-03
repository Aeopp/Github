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
#include "../CMath.h"
#include "../Pixel.h"
#include "../DataTable.h"
#include "Object/Mouse.h"

void CCore::Clear()
{
	
}

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

#ifdef _DEBUG
	FreeConsole();
#endif
}

bool CCore::Init(HINSTANCE hInst)
{
	m_hInst = hInst;
	MyRegisterClass(); 

	m_tRS.iW = 1280;
	m_tRS.iH = 720;
	Create();

	m_hDC = GetDC(m_hWnd);

	if (!GET_SINGLE(CTimer)->Init(m_hWnd)){
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
		m_tRS, RESOLUTION(Stage::SizeWidth, Stage::SizeHeight))){
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
	case WM_SETCURSOR:{
		
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
	if (Update(fDeltaTime) == SC_CHANGE) {
		return; 
	}
	if ( LateUpdate(fDeltaTime) ==SC_CHANGE) {
		return; 
	}
	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
	GET_SINGLE(CInput)->Update(fDeltaTime);
	GET_SINGLE(CSceneManager)->Input(fDeltaTime);
	GET_SINGLE(CCamera)->Input(fDeltaTime); 
}

SCENE_CHANGE CCore::Update(float fDeltaTime)
{
	SCENE_CHANGE sc;

	sc = GET_SINGLE(CSceneManager)->Update(fDeltaTime);
	GET_SINGLE(CCamera)->Update(m_hDC,fDeltaTime);
	return sc;
}

SCENE_CHANGE CCore::LateUpdate(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);

	if (CObj::m_ObjList.size() < 2) {
		return sc; 
	}

	for (auto Outer = std::begin(CObj::m_ObjList);
		Outer != std::end(CObj::m_ObjList); ++Outer) {

		auto Inner = Outer;
		std::advance(Inner, 1);

		for (Inner; Inner != std::end(CObj::m_ObjList); ++Inner) {

			if ((*Inner)->GetCollisionTag() == ECollision_Tag::Rect &&
				(*Outer)->GetCollisionTag() == ECollision_Tag::Rect) {

				auto LhsRect = (*Inner)->GetCollisionRect();
				auto RhsRect = (*Outer)->GetCollisionRect();
				if (false == CollisionRectToRect(LhsRect, RhsRect)) {
					auto LhsTag = (*Inner)->GetTag();
					auto RhsTag = (*Outer)->GetTag();

					if (LhsTag == L"Stage" || RhsTag == L"Stage")continue;

					auto InnerHitList = (*Inner)->GetHitList();
					auto inner_find=  std::find_if(std::begin(InnerHitList), std::end(InnerHitList),
						[&](auto Pair) {return Pair.first == *Outer; });


					auto OuterHitList = (*Outer)->GetHitList();
					auto outer_find = std::find_if(std::begin(OuterHitList), std::end(OuterHitList),
						[&](auto Pair) {return Pair.first == *Inner;  });

					if (inner_find != std::end(InnerHitList)) {
						(*Inner)->ReleaseHitEvent(*Outer, fDeltaTime);
					}
					if (outer_find != std::end(OuterHitList)) {
						(*Outer)->ReleaseHitEvent(*Inner, fDeltaTime);
					}
				}
			}
		}
	}
	return sc;
}

void CCore::Collision(float fDeltaTime)
{
	// TODO :: ���⼭ �浹 �˻��ϱ����� ���̺� ���� ���� ������� !!!!!!!!!!!!
	GET_SINGLE(CSceneManager)->Collision(fDeltaTime);

	if (CObj::m_ObjList.size() < 2) {
		return; 
	}

	for (auto Outer = std::begin(CObj::m_ObjList);
		Outer != std::end(CObj::m_ObjList);++Outer) {

		auto Inner = Outer;
		std::advance(Inner, 1);

		for (Inner; Inner != std::end(CObj::m_ObjList); ++Inner) {

			if ((*Inner)->GetCollisionTag() == ECollision_Tag::Rect &&
				(*Outer)->GetCollisionTag() == ECollision_Tag::Rect) {

				auto LhsRect = (*Inner)->GetCollisionRect();
				auto RhsRect = (*Outer)->GetCollisionRect();
				if (true == CollisionRectToRect(LhsRect, RhsRect)) {
					auto LhsTag = (*Inner)->GetTag();
					auto RhsTag = (*Outer)->GetTag();

					if (LhsTag == L"Stage" || RhsTag == L"Stage")continue;

					if (auto InnerPair = (*Inner)->FindHitList(*Outer); InnerPair.first != nullptr) {
						InnerPair.second = ECOLLISION_STATE::Release;
					}
					if (auto OuterPair = (*Outer)->FindHitList(*Inner); OuterPair.first != nullptr) {
						OuterPair.second = ECOLLISION_STATE::Release;
					}

					(*Inner)->Hit(*Outer, fDeltaTime);
					(*Outer)->Hit(*Inner, fDeltaTime);
					//MessageBox(NULL, LhsTag.c_str(), RhsTag.c_str(),MB_OK);
				}
			}
			else if ( ((*Inner)->GetCollisionTag() == ECollision_Tag::Rect &&
				     (*Outer)->GetCollisionTag() == ECollision_Tag::Pixel  )
						) {
				auto LhsRect = (*Inner)->GetCollisionRect();
				CPixel* RhsPixel = static_cast<CPixel*>(*Outer);
					auto _Pixel = 	RhsPixel->GetPixel();

				if (true == CollisionRectToPixel(LhsRect, _Pixel, RhsPixel->GetWidth(),
					RhsPixel->GetHeight())) {
					auto LhsTag = (*Inner)->GetTag();
					auto RhsTag = (*Outer)->GetTag();

					if (LhsTag == L"Stage" || RhsTag == L"Stage")continue;

					(*Inner)->Hit(*Outer, fDeltaTime);
					(*Outer)->Hit(*Inner, fDeltaTime);
					MessageBox(NULL, LhsTag.c_str(), RhsTag.c_str(),MB_OK);
				}
			}
			else if (((*Outer)->GetCollisionTag() == ECollision_Tag::Rect &&
			(*Inner)->GetCollisionTag() == ECollision_Tag::Pixel)
			) {
			auto LhsRect = (*Outer)->GetCollisionRect();
			CPixel* RhsPixel = static_cast<CPixel*>(*Inner);
			auto _Pixel = RhsPixel->GetPixel();

			if (true == CollisionRectToPixel(LhsRect, _Pixel,RhsPixel->GetWidth(),
				RhsPixel->GetHeight())) {
				auto LhsTag = (*Inner)->GetTag();
				auto RhsTag = (*Outer)->GetTag();

				if (LhsTag == L"Stage" || RhsTag == L"Stage")continue;

				(*Inner)->Hit(*Outer, fDeltaTime);
				(*Outer)->Hit(*Inner, fDeltaTime);
				MessageBox(NULL, LhsTag.c_str(), RhsTag.c_str(),MB_OK);
			    }
			}
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


	// ���׹��׹���
	//GET_SINGLE(CCollisionManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
	CTexture* pBackBuffer = GET_SINGLE(CResourcesManager)->GetBackBuffer();

	//Rectangle(pBackBuffer->GetDC(), 0, 0, GETRESOLUTION.iW, GETRESOLUTION.iH);
	//
	GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDC(),fDeltaTime);

	CMouse* pMouse = GET_SINGLE(CInput)->GetMouse();

	pMouse->Render(pBackBuffer->GetDC(),
		fDeltaTime);

	BitBlt(m_hDC, 0, 0, GETRESOLUTION.iW, GETRESOLUTION.iH, pBackBuffer->GetDC(),
		0, 0, SRCCOPY);

	SAFE_RELEASE(pBackBuffer); 
}

bool CCore::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest)
{
	if (src.left > dest.right)
		return false;
	else if (src.right < dest.left)
		return false;
	else if (src.top > dest.bottom)
		return false;
	else if (src.bottom < dest.top)
		return false;

	return true;
}

bool CCore::CollisionRectToPoint(const RECTANGLE& src, const POSITION& dest)
{
	if (dest.x < src.left)
		return false;
	else if (dest.x > src.right)
		return false;
	else if (dest.y < src.top)
		return false;
	else if (dest.y > src.bottom)
		return false; 
	return true ;
}

bool CCore::CollisionSphereToPoint(const RECTANGLE& src, const POSITION& dest)
{
	return CMath::Distance(dest, { (src.right + src.left) / 2,
		(src.bottom + src.top) / 2 });
}

bool CCore::CollisionSphereToPixel(const RECTANGLE& src, const vector<PIXEL>& vecPixel, int iWidth, int iHeight)
{
	return false;
}

bool CCore::CollisionPixelToPoint(const vector<PIXEL>& vecPixel, int iWidth, int iHeight, const POSITION& dest)
{
	return false;
}

bool CCore::CollisionSphereToSphere(const RECTANGLE& Lhs, const RECTANGLE& Rhs)
{
	POSITION LhsCenter{
		(Lhs.right + Lhs.left)/2,
		(Lhs.bottom + Lhs.top )/2};

	POSITION RhsCenter{
		(Rhs.right+Rhs.left)/2,
		(Rhs.bottom+Rhs.top)/2};

	float fDist = CMath::Distance(LhsCenter, RhsCenter);

	float LhsRadius = Lhs.right - LhsCenter.x;

	float RhsRadius = Rhs.right - RhsCenter.x;

	return fDist <= LhsRadius + RhsRadius;
}

bool CCore::CollisionRectToPixel(const RECTANGLE& src, const vector<PIXEL>& vecPixel, int iWidth, int iHeight)
{
	int iStartX, iEndX;
	int iStartY, iEndY;

	iStartX = src.left < 0 ? 0 : src.left;
	iEndX = src.right >= iWidth ?
		iWidth - 1 : src.right;

	iStartY = src.top < 0 ? 0 : src.top;
	iEndY = src.bottom >= iHeight? iHeight - 1:
		src.bottom;

	for (int i = iStartY; i <= iEndY; ++i) {
		for (int j = iStartX; j <= iStartX; ++j) {
			int idx = i * iWidth + j;
			const PIXEL& pixel = vecPixel[idx];
			if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255) {
				
				return true; 
			}
		}
	}

	return false; 
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

		RECT rc = { 0,0,GETRESOLUTION.iW,GETRESOLUTION.iH};
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
#ifdef _DEBUG
	AllocConsole();
#endif
};

CCore::~CCore() noexcept
{
	/*DESTROY_SINGLE(CCore);
	DESTROY_SINGLE(CTimer);*/
	//DESTROY_SINGLE(CTimer);
}

