#pragma once
#include "Game.h"
#include "../include/Core/PathManager.h"

class CCore
{
private:
	static inline CCore* m_pInst;
	static inline bool m_bLoop = true;
	static inline HINSTANCE m_hInst;
	static inline HWND m_hWnd;
	static inline HDC m_hDC;
	RESOLUTION m_tRS;
public:
	RESOLUTION GetResolution()const {
		return m_tRS;
	}
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
	 
	bool CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest)
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
	};

	ATOM MyRegisterClass(); 
	BOOL Create();
private:
	CCore();
	~CCore()noexcept;
};

