#pragma once
#include "include/Core/Ref.h"
#include "include/Resources/Texture.h"
#include "include/Resources/ResourcesManager.h"

class CAnimation : 
	public CRef
{
private:
	friend class CObj;
	CAnimation();
	CAnimation(const CAnimation& anim);
	~CAnimation(); 
private:
	unordered_map<wstring, PANIMATIONCLIP > m_mapClip;

	PANIMATIONCLIP m_pCurClip;
	wstring m_strCurClip;
	wstring m_strDefaultClip;
	class CObj* m_pObj;
public:
	PANIMATIONCLIP GetCurrentClip()const {
		return m_pCurClip;
	}
	void SetObj(class CObj* pObj) {
		m_pObj = pObj;
	}
	bool AddClip(const wstring& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption,float fAnimationLimitTime,
		int iFrameMaxX,int iFrameMaxY,int iStartX, int iStartY,
		int iLengthX , int iLengthY , float fOptionLimitTime,
		const wstring& strTexKey ,const wchar_t* pFileName,
		const wstring& strPathKey = TEXTURE_PATH);

	void SetClipColorkey(const wstring& strClip ,unsigned char r,
		unsigned char g, unsigned char b);

	void SetCurrentClip(const wstring& strCurClip);
	void SetDefaultClip(const wstring& strDefaultClip);
	void ChangeClip(const wstring& strClip);
private:
	PANIMATIONCLIP FindClip(const wstring strName);
public:
	bool Init();
	void Update(float fTime);
	CAnimation* Clone();
};

