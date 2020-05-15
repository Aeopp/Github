#include "framework.h"
#include "Made.h"
#include "utility"
#include <vector>activation.h
#include <string>activecf.h
#include <sstream>
#include "game.h"
#include "Time.h"
#include "setup.h"
// 전역 변수:

// 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MADE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MADE));
    MSG msg;
    window::hdc = std::shared_ptr<HDC__>(GetDC(window::hWnd),window::_ReleaseDC);
    
    // 기본 게임 루프입니다:
    while (game::Instance().bLoop==true)
    {
        // PeekMessage 는 데드타임에도 작동합니다.
        // 메시지큐에 메시지가 남아있습니다.
        if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))  {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // 메시지큐에 메시지가 없습니다. (게임 진행)
        else {
            Time::Instance().Update();
            game::Instance().Run();
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
	
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MADE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MADE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance ,int nCmdShow)
{
   window::hInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   setup::ResoluctionHeight = 1600;
   setup::ResoluctionHeight = 900;

   window:: hWnd = CreateWindowW(
       szWindowClass, 
       szTitle, 
       WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 
       setup::ResoluctionWidth, 
       setup::ResoluctionHeight, 
       nullptr, nullptr, 
       hInstance, nullptr);

   if (!window::hWnd)
       return FALSE;

   RECT Rect{ 0,0,setup::ResoluctionWidth,setup::ResoluctionHeight };
   // 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를 구해줍니다.
   AdjustWindowRect(&Rect, WS_OVERLAPPED, FALSE);
   // 윈도우 클라 영역의 크기를 원하는 크기로 맞춰줍니다.
   SetWindowPos(window::hWnd, HWND_TOPMOST, 0, 0,
       Rect.right - Rect.left, Rect.bottom -Rect.top, SWP_NOMOVE|SWP_NOZORDER);
   
   ShowWindow(window::hWnd, nCmdShow);
   UpdateWindow(window::hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, const UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case WM_CHAR:
                break;
            case IDM_ABOUT:
                DialogBox(window::hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CHAR:
      
        break; 
    case WM_PAINT:
        {
            PAINTSTRUCT pain_struct;
            HDC hdc = BeginPaint(hWnd, &pain_struct);
            // TODO :: 여기에 Draw
            std::wstringstream Wss;
            auto Mouse_start = window::format_text(L"Start : x ", window::MouseArea.Start.first
                , L" y : ", window::MouseArea.Start.second);

            auto Mouse_end = window::format_text(L"End : x ", window::MouseArea.End.first
                , L" y : ", window::MouseArea.End.second);

            if (window::MouseArea.bStart) {
                   Rectangle(hdc, 
                  window::MouseArea.Start.first, window::MouseArea.Start.second, window::MouseArea.End.first, window::MouseArea.End.second);
            }
            RECT Rect;
            GetClientRect(window::hWnd, &Rect);

            TextOut(hdc, Rect.right/2,Rect.bottom/10, Mouse_start.c_str(), Mouse_start.size());
            TextOut(hdc, Rect.right/ 2, Rect.bottom/ 8, Mouse_end.c_str(), Mouse_end.size());
            EndPaint(hWnd, &pain_struct);
        }
        break;
    case WM_MOUSEMOVE:
        if (window::MouseArea.bStart == true) {
            window::MouseArea.End = window::GetMousePos(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONUP:
        if (window::MouseArea.bStart == true) {
            window::MouseArea.bStart = false; 
            window::MouseArea.End = window::GetMousePos(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONDOWN:
    	 if(window::MouseArea.bStart==false) {
             window::MouseArea.bStart = true;
             window::MouseArea.End = 
             window::MouseArea.Start = window::GetMousePos(lParam);
             InvalidateRect(hWnd, NULL, TRUE);
    	 }
            break; 
    case WM_DESTROY:
        PostQuitMessage(0);
        game::Instance().bLoop = false; 
        break;
    case WM_KEYDOWN:
    //   DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
