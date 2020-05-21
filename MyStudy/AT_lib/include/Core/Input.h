#pragma once
#include "../Game.h"

struct KEYINFO {
	vector<DWORD> vecKey;
	bool bDown; 
	bool bPress;
	bool bUp;

	KEYINFO() :
		bDown(false),
		bPress{ false },
		bUp{ false }{};
};

class CInput
{
private:
	HWND m_hWnd; 
	std::unordered_map<string, KEYINFO*> m_mapKey;
public:
	bool Init(HWND hWnd);
	DECLARE_SINGLE(CInput)
};

