#include "Input.h"
DEFINTION_SINGLE(CInput)

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey(VK_SPACE, "Jump");
	AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");
	AddKey("MoveLeft", VK_LEFT);
	AddKey("MoveRight", VK_RIGHT);
	AddKey("Fire", VK_SPACE);
	AddKey(VK_CONTROL, "Skill1", '1');

	return true; 
}

void CInput::Update(float fDeltaTime)
{
	for (auto iter = m_mapKey.begin(); iter != std::end(m_mapKey); ++iter) {
		int iPushCount = 0;   
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i) {
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000) {
				++iPushCount;
			}
			if (iPushCount == iter->second->vecKey.size()) {
				if (!iter->second->bDown && !iter->second->bPress) {
					iter->second->bPress = true;
					iter->second->bDown = true;
				}
				else if(iter->second->bDown){
					iter->second->bPress = true;
				}
			}
			else {
				if (iter->second->bDown || iter->second->bPress) {
					iter->second->bUp = true;
					iter->second->bDown = false;
					iter->second->bPress = false;  
				}
				else if (iter->second->bUp) {
					iter->second->bUp = false;
				}
			}
		}
	}
}

bool CInput::KeyDown(const string& strKey) const&
{
	KEYINFO* pInfo = FindKey(strKey);
	if (pInfo == nullptr) {
		return false;
	}
	return pInfo->bDown;
}

bool CInput::KeyPress(const string& strKey) const&
{
	KEYINFO* pInfo = FindKey(strKey);
	if (pInfo == nullptr) {
		return false;
	}
	return pInfo->bPress;
}

bool CInput::KeyUp(const string& strKey) const&
{
	KEYINFO* pInfo = FindKey(strKey);
	if (pInfo == nullptr) {
		return false;
	}
	return pInfo->bUp;
}

KEYINFO* CInput::FindKey(const string& strKey)const
{
	if (auto iter = m_mapKey.find(strKey);
		iter==std::end(m_mapKey)){
		return nullptr;
	}
	else {
		return iter->second;
	}
}

CInput::CInput():
	m_pCreateKey{ nullptr }
{
	
}

CInput::~CInput() noexcept
{
}
