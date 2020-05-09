#pragma once
#include "TStd.h"
enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP};
class TInput : public TSingleton<TInput>
{
	friend class TSingleton<TInput>;
	DWORD       m_dwKeyState[256];
	POINT		m_MousePos;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	DWORD		KeyCheck(DWORD dwKey);
private:
	TInput();
public:
	~TInput();
};

#define I_Input TInput::GetInstance()