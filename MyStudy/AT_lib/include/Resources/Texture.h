#pragma once
#include "../Core/Ref.h"
class CTexture :
	public CRef
{
private:
	friend class CResourcesManager;

	
private:
	HDC m_hMemDC;
	HBITMAP m_hBitmap; 
	HBITMAP m_hOldBitmap; 
	BITMAP m_tInfo;
public:
	CTexture();
	~CTexture();
	bool LoadTexture(HINSTANCE hInst,HDC hDC,
	const wstring& strKey , const wchar_t*
	pFileName , const wstring& strPathKey=TEXTURE_PATH );      
	HDC GetDC()const {
		return m_hMemDC;
	}
};

