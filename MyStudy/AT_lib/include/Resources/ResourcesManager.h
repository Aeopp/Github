#pragma once
#include "../Game.h"
class CResourcesManager
{
private:
	unordered_map<wstring, class CTexture*>
		m_mapTexture;
	HINSTANCE m_hInst;
	HDC m_hDC;
public:
	bool Init(HINSTANCE
		hInst,HDC hDC); 
	class CTexture* LoadTexture(
		const wstring& strKey, const wchar_t*
		pFileName, const wstring& strPathKey=TEXTURE_PATH);
	class CTexture* FindTexture(const
		wstring& strKey);
	DECLARE_SINGLE(CResourcesManager)
};

