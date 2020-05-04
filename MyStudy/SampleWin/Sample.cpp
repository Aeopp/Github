#include "Sample.h"

// 윈도우 프로시저
// 윈도우에서 이벤트가 발생할때마다 호출
LRESULT CALLBACK xxxxx(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM TParam) {
	
	switch (msg) {
		// WM_DESTROY = Window 종료버튼을 눌렀을때
	case WM_DESTROY:
		// window msg queue 에 post 에
		// WM_QUITMESSAGE 를 추가한다
		PostQuitMessage(0);
		break;
	default :
		break;
	};
	// Client 에서 처리하지 못한 msg 에 대한 처리를
	// 윈도우의 Default 처리 함수에 따라서 처리한다.
	return DefWindowProc(hWnd, msg, wParam, TParam);
};
// 유니코드 사용 wWinMain                 
int WINAPI wWinMain(HINSTANCE
	hInstance, HINSTANCE,LPWSTR,int)
{
	WNDCLASSEXW wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hInstance = HINSTANCE;
	// 가로 세로 Draw 
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 클래스 이름으로 등록 하였기 때문에
	// 다음에 찾을때 이 이름으로 찾아야함
	wc.lpszClassName = L"KGCAWIN";
	// 프로시저 등록
	wc.lpfnWndProc = xxxxx;
	// 백그라운드 Color 를 설정한다.
	//wc.hbrBackground = 
	//(HBRUSH)GetStockObject(WHITE_BRUSH);
	//// 마우스 커서 세팅
	//wc.hCursor = LoadCursor(NULL, IDC_IBEAM);
	//// 윈도우 창 아이콘을 바꾼다.
	//wc.hIcon = LoadIcon(NULL, IDI_QUESTION); 
	// WNCCLASSEXW 구조체의 내용을 바탕으로 등록
	if (RegisterClassEx(&wc)==false) {
		return 1;
	}
	// 2. 등록된 윈도우 클래스로 윈도우 생성
	// 하나의 프로세스에서 여러개의 윈도우 창을
	// 띄울수 있으며 각각의 윈도우 창을 관리하는 핸들을
	// 반환한다.
	auto hWnd = CreateWindowExW(
		_In_ DWORD dwExStyle,
		/*WNDCLASSEXW 이름으로 반드시 설정*/
		//_In_opt_ LPCWSTR lpClassName,
		L"KGCAWIN",
		/*_In_opt_ LPCWSTR lpWindowName,*/
		// 내가 하고싶은 이름으로 설정
		L"SAMPLEWINDOW",
		WS_OVERLAPPEDWINDOW,
		//_In_ DWORD dwStyle,
		
		// 윈도우의 시작 좌표와 크기를 설정한다.
		/*_In_ int X,
		_In_ int Y,
		_In_ int nWidth,
		_In_ int nHeight,*/
		100,100,300, 300,

		_In_opt_ HWND hWndParent,
		_In_opt_ HMENU hMenu,
		_In_opt_ HINSTANCE hInstance,
		_In_opt_ LPVOID lpParam);

	//GetMessage(&msg) = 운영체제의 MessageQueue 에서
	// 메시지를 가지고 온다. (키가 눌렸다는것을 알려준다)
	// GetMessage window msg queue 에서 큐가
	// 비었을 경우 GetMessage 는 리턴하지않고 대기한다
	// 즉 게임에서는 쓸모가 없다...

	//PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)
	//	PM_REMOVE 파라미터를 지정해주면
	// 메시지 큐에서 메시지를 가져온 이후 큐에서 메시지를 지우며
	// 지정하지 않으면 지우지 않는다.

	// Translatemessage(&msg) ; 
	// 해당 키를 해석한다 (무슨 키가 눌렸는지)

	// DispatchMessage(&msg)
	// 해당 메시지를 바탕으로 윈도우 프로시저를 호출한다.
	// 메시지를 전부 처리 하고나서 Frame Render 를 호출한다
	
	auto Run = []{}; 

	while (true) {

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			if (msg.message == WM_QUIT) 
				break;
			else {
				Run();
				/*CoreFrame();
				CoreRender();*/
			}
		}
	}
	return 0; 
};
