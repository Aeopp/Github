#include "CCore.h"
#include "Scene/CSceneManager.h"
#include "Core/Timer.h"

void CCore::DestroyInst() {
	SAFE_DELETE(m_pInst);
	DESTROY_SINGLE(CTimer); 
	//SAFE_DELETE(m_pInst);
}

bool CCore::Init(HINSTANCE hInst)
{
	m_hInst = hInst;
	MyRegisterClass(); 

	m_tRs.iW = 1280;
	m_tRs.iH = 720;
	Create();

	m_hDC = GetDC(m_hWnd);

	if (!GET_SINGLE(CTimer)->Init()){
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
	GET_SINGLE(CSceneManager)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->Update(fDeltaTime);

	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);

	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->Render(m_hDC,fDeltaTime);
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

		RECT rc = { 0,0,m_tRs.iW,m_tRs.iH};
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

};

CCore::~CCore() noexcept
{
	/*DESTROY_SINGLE(CCore);
	DESTROY_SINGLE(CTimer);*/
}

