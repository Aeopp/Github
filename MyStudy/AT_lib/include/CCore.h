#pragma once
#include "Game.h"

class CCore
{
private:
	static inline CCore* m_pInst;
	static inline bool m_bLoop = true;
	HINSTANCE m_hInst;
	HWND m_hWnd; 
	HDC m_hDC;
	Resolution m_tRs;
public:
	static CCore* GetInst() {
		if (!m_pInst)
			m_pInst = new CCore{};
		return  m_pInst;
	};
	static void DestroyInst();
	bool Init(HINSTANCE hInst);
	int Run();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam); 
private :
	void Logic(); 
	void Input(float fDeltaTime );
	int Update(float fDeltaTime); 
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);
	 
	ATOM MyRegisterClass(); 
	BOOL Create();
private:
	CCore();
	~CCore()noexcept;
};

