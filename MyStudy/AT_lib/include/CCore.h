#pragma once
#include "Game.h"
#include "../include/Core/PathManager.h"
#include "../include/Types.h"
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
	 
	bool CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest);;

	// 구체 만들어서 구체로 바꾸기
	bool CollisionSphereToSphere(const RECTANGLE& Lhs, const RECTANGLE& Rhs);

	bool CollisionRectToPixel(const RECTANGLE& src, const vector<PIXEL>& vecPixel,int iWidth,int iHeight);

	ATOM MyRegisterClass(); 
	BOOL Create();
private:
	CCore();
	~CCore()noexcept;
};

