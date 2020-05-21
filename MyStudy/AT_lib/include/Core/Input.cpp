#include "Input.h"
DEFINTION_SINGLE(CInput)

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	return true; 
}

CInput::CInput()
{
	
}

CInput::~CInput() noexcept
{
}
