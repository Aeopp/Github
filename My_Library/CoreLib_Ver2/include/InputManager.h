#pragma once
#include "Utility.h"
enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP};
class TInput : public SingleTon<TInput>
{
	friend class SingleTon<TInput>;
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

#define I_Input TInput::Instance()