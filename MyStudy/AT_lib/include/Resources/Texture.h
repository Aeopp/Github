#pragma once
#include "../Core/Ref.h"
class CTexture :
	public CRef
{
private:
	friend class CResourcesManager;

	CTexture();
	~CTexture();
private:
	HDC m_hMemDC;
public:
	bool LoadTexture(HINSTANCE hInst,HDC hDC,
	const wstring& strKey , const wchar_t*
	pFileName , const wstring& strPathKey=TEXTURE_PATH );        
};

