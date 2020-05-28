#include "Input.h"
#include "../Object/Mouse.h"
#include "../../CAnimation.h"
#include "../Scene/Layer.h"

DEFINTION_SINGLE(CInput)

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey(VK_SHIFT, "Jump");
	/*AddKey('W', "MoveFront");
	AddKey('S', "MoveBack");*/
	AddKey("MoveLeft", VK_LEFT);
	AddKey("MoveRight", VK_RIGHT);
	AddKey("Fire", 'Q');
	AddKey(VK_CONTROL, "Skill1", '1');

	AddKey(VK_CONTROL, "Attack");
	AddKey(VK_LBUTTON, "MouseLButton");
	AddKey('A', "Attack2");
	AddKey('S', "Attack3");
	AddKey('D', "Attack4");

	AddKey(VK_ESCAPE, "Dead");

	AddKey('1', "Click");
	AddKey('2', "Mushroom");
	AddKey('3', "Placement");

	GetCursorPos(&m_tMousePos);

	m_pMouse = CObj::CreateObj<CMouse>
		(L"Mouse");
	
	m_pMouse->SetSize(32, 32);


	CAnimation* pAni = m_pMouse->CreateAnimation(L"MouseAnimation");
	
	m_pMouse->AddAnimationClip(L"MouseNormal", AT_ATLAS, AO_LOOP,
			1.0f, 1, 1, 0, 0, 1, 1, 0.f, L"MouseNormal", L"Mouse\\1.bmp");

	m_pMouse->SetAnimationClipColorkey(L"MouseNormal", 255, 0, 255);


	m_pMouse->AddAnimationClip(L"MouseClick", AT_ATLAS, AO_LOOP,
		1.0f, 1, 1, 0, 0, 1, 1, 0.f, L"MouseClick", L"Mouse\\2.bmp");

	m_pMouse->SetAnimationClipColorkey(L"MouseClick", 255, 0, 255);


	m_pMouse->AddAnimationClip(L"MousePlacement", AT_ATLAS, AO_LOOP,
		1.0f, 1, 1, 0, 0, 1, 1, 0.f, L"MousePlacement", L"Mouse\\3.bmp");

	m_pMouse->SetAnimationClipColorkey(L"MousePlacement", 255, 0, 255);



	m_pMouse->AddAnimationClip(L"Mouse4", AT_ATLAS, AO_LOOP,
		1.0f, 1, 1, 0, 0, 1, 1, 0.f, L"Mouse4", L"Mouse\\4.bmp");

	m_pMouse->SetAnimationClipColorkey(L"Mouse4", 255, 0, 255);


	m_pMouse->AddAnimationClip(L"Mouse5", AT_ATLAS, AO_LOOP,
		1.0f, 1, 1, 0, 0, 1, 1, 0.f, L"Mouse5", L"Mouse\\5.bmp");

	m_pMouse->SetAnimationClipColorkey(L"Mouse5", 255, 0, 255);



	m_pMouse->AddAnimationClip(L"Mouse6", AT_ATLAS, AO_LOOP,
		1.0f, 1, 1, 0, 0, 1, 1, 0.f, L"Mouse6", L"Mouse\\6.bmp");

	m_pMouse->SetAnimationClipColorkey(L"Mouse6", 255, 0, 255);



	m_pMouse->AddAnimationClip(L"MouseMushroom", AT_ATLAS, AO_LOOP,
		1.0f, 1, 1, 0, 0, 1, 1, 0.f, L"MouseMushroom", L"Mouse\\7.bmp");

	m_pMouse->SetAnimationClipColorkey(L"MouseMushroom", 255, 0, 255);


	SAFE_RELEASE(pAni);

	m_pMouse->m_pAnimation->ChangeClip(L"MouseNormal");
	m_pMouse->m_pAnimation->SetDefaultClip(L"MouseNormal");
	m_pMouse->bBorder = false;
	ShowCursor(false); 


		 // FRAMEANIMATION 
		{
			/*CAnimation* pAni = m_pMouse->CreateAnimation(L"MouseNormal");

		vector<wstring> vecFileName;

		for (int i = 1; i <= 1; ++i) {
			wchar_t strFileName[MAX_PATH] = {};
			wsprintf(strFileName, L"MouseNormal", L"Mouse/%d.bmp", i);
			vecFileName.push_back(strFileName);
		}

		m_pMouse->AddAnimationClip(L"MouseNormal", AT_FRAME, AO_LOOP,
			1.f, 1, 1, 0, 0, 1, 1, 0.f, L"MouseNormal", vecFileName);
		m_pMouse->SetAnimationClipColorkey(L"MouseNormal", 255, 0, 255);*/

		//   SAFE_RELEASE(pAni);
		}
		
	return true;
};

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

	m_pMouse->Update(fDeltaTime);
	m_pMouse->LateUpdate(fDeltaTime);

	
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

 void CInput::MouseAnimPlay(const string& Tag)& {
	if (Tag == "Click") {
		m_pMouse->m_pAnimation->ChangeClip(L"MouseCick");
		m_pMouse->m_pAnimation->SetDefaultClip(L"MouseCick");
	}
	else if (Tag == "Mushroom") {
		m_pMouse->m_pAnimation->ChangeClip(L"MouseMushroom");
		m_pMouse->m_pAnimation->SetDefaultClip(L"MouseMushroom");
	}
	else if (Tag == "Placement") {
		m_pMouse->m_pAnimation->ChangeClip(L"MousePacement");
		m_pMouse->m_pAnimation->SetDefaultClip(L"MouseMushroom");
	}
	if (Tag == "Mouse4") {
		m_pMouse->m_pAnimation->ChangeClip(L"Mouse4");
		m_pMouse->m_pAnimation->SetDefaultClip(L"Mouse4");
	}
	else if (Tag == "Mouse5") {
		m_pMouse->m_pAnimation->ChangeClip(L"Mouse5");
		m_pMouse->m_pAnimation->SetDefaultClip(L"Mouse5");
	}
	else if (Tag == "Mouse6") {
		m_pMouse->m_pAnimation->ChangeClip(L"Mouse6");
		m_pMouse->m_pAnimation->SetDefaultClip(L"Mouse6");
	}
	else	if (Tag == "MouseNormal") {
		m_pMouse->m_pAnimation->ChangeClip(L"MouseNormal");
		m_pMouse->m_pAnimation->SetDefaultClip(L"MouseNormal");
	}

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
	m_pCreateKey{ nullptr },
	m_pMouse{ nullptr }
{
	
}

CInput::~CInput() noexcept
{
	CObj::EraseObj(m_pMouse);
	SAFE_RELEASE(m_pMouse);
	Safe_Release_Map(m_mapKey);
}
