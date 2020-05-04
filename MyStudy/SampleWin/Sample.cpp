#include "Sample.h"

// ������ ���ν���
// �����쿡�� �̺�Ʈ�� �߻��Ҷ����� ȣ��
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM TParam) {
	
	switch (msg) {
		// WM_DESTROY = Window �����ư�� ��������
	case WM_DESTROY:
		// window msg queue �� post ��
		// WM_QUITMESSAGE �� �߰��Ѵ�
		PostQuitMessage(0);
		break;
	default :
		break;
	};
	// Client ���� ó������ ���� msg �� ���� ó����
	// �������� Default ó�� �Լ��� ���� ó���Ѵ�.
	return DefWindowProc(hWnd, msg, wParam, TParam);
};
// �����ڵ� ��� wWinMain                 
int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPWSTR	lpCmdLine,
					int    nCmdShow)
{
	// ������ ������ Ŭ���� �ü�� ���
	WNDCLASSEXW wc;
	ZeroMemory(&wc,sizeof(WNDCLASSEXW));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hInstance = hInstance;
	// ���� ���� Draw 
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// Ŭ���� �̸����� ��� �Ͽ��� ������
	// ������ ã���� �� �̸����� ã�ƾ���
	wc.lpszClassName = L"KGCAWIN";
	// ���ν��� ���
	wc.lpfnWndProc = WndProc;
	wc.lpfnWndProc= WndProc;
	// ��׶��� Color �� �����Ѵ�.
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	//// ���콺 Ŀ�� ����
	//wc.hCursor = LoadCursor(NULL, IDC_IBEAM);
	//// ������ â �������� �ٲ۴�.
	//wc.hIcon = LoadIcon(NULL, IDI_QUESTION); 
	// WNCCLASSEXW ����ü�� ������ �������� ���
	if (RegisterClassEx(&wc)==false) {
		return 1;
	}
	// 2. ��ϵ� ������ Ŭ������ ������ ����
	// �ϳ��� ���μ������� �������� ������ â��
	// ���� ������ ������ ������ â�� �����ϴ� �ڵ���
	// ��ȯ�Ѵ�.
	auto hWnd = CreateWindowExW(0,
		/*WNDCLASSEXW �̸����� �ݵ�� ����*/
		//_In_opt_ LPCWSTR lpClassName,
		L"KGCAWIN",
		/*_In_opt_ LPCWSTR lpWindowName,*/
		// ���� �ϰ���� �̸����� ����
		L"SAMPLEWINDOW",
		WS_OVERLAPPEDWINDOW,
		//_In_ DWORD dwStyle,

		// �������� ���� ��ǥ�� ũ�⸦ �����Ѵ�.
		/*_In_ int X,
		_In_ int Y,
		_In_ int nWidth,
		_In_ int nHeight,*/
		100, 100, 300, 300, 0, 0, hInstance, 0);

	if (hWnd == NULL)return 1;
	ShowWindow(hWnd, SW_SHOW);
	//GetMessage(&msg) = �ü���� MessageQueue ����
	// �޽����� ������ �´�. (Ű�� ���ȴٴ°��� �˷��ش�)
	// GetMessage window msg queue ���� ť��
	// ����� ��� GetMessage �� ���������ʰ� ����Ѵ�
	// �� ���ӿ����� ���� ����...

	//PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)
	//	PM_REMOVE �Ķ���͸� �������ָ�
	// �޽��� ť���� �޽����� ������ ���� ť���� �޽����� �����
	// �������� ������ ������ �ʴ´�.

	// TranslateMessage(&msg) ; 
	// �ش� Ű�� �ؼ��Ѵ� (���� Ű�� ���ȴ���)

	// DispatchMessage(&msg)
	// �ش� �޽����� �������� ������ ���ν����� ȣ���Ѵ�.
	// �޽����� ���� ó�� �ϰ��� Frame Render �� ȣ���Ѵ�

	MSG msg;

	auto Run{ [] {} };
	
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
