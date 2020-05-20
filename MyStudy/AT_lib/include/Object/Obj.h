#pragma once
#include "../Core/Ref.h"
#include "../Types.h"
#include "../Scene/Layer.h"
class CObj : public CRef
{
protected:
	CObj();
	CObj(const CObj& Obj);
public:
	static inline list<CObj*> m_ObjList;
	
public:
	virtual ~CObj();
	static void AddObj(CObj* pObj);
	static CObj* FindObject(const wstring& strTag);
	// Iter 갱신 로직 체크 바람 ++Iter 지워야 할수도 있음
	static void EraseObj(CObj* pObj);
	static void EraseObj(const wstring& strTag);
	static void EraseObj();
	
protected:
	int m_iRef;
	wstring m_strTag;
	POSITION m_tPos;
	_SIZE m_tSize;
	POSITION m_tPivot;
	class CScene* m_pScene;
	class CLayer* m_pLayer;
	class CTexture* m_pTexture;
public:
	void SetScene(class CScene* pScene) {
		m_pScene = pScene;
	}
	void SetLayer(class CLayer* pLayer) {
		m_pLayer = pLayer;
	}
	class CScene* GetScene(class CScene* pScene) const {
		return m_pScene;
	}
	class CLayer* GetLayer(class CLayer* pLayer)const {
		return m_pLayer;
	}
	wstring GetTag()const {
		return m_strTag;
	}
	POSITION GetPos()const {
		return m_tPos;
	}
	_SIZE GetSize()const {
		return m_tSize;
	};
public:
	float GetLeft()const {
		return m_tPos.x - m_tSize.x * m_tPivot.x;
	}
	float GetRight() const {
		return GetLeft() + m_tSize.x;  
	}
	float GetTop() const {
		return m_tPos.y - m_tSize.y * m_tPivot.y; 
	}
	float GetBottom() const {
		return GetTop() + m_tSize.y; 
	}
	POSITION GetCenter() const {
		return POSITION(GetLeft() + m_tSize.x / 2.f,
			GetTop() + m_tSize.y / 2.f);
	};
	POSITION GetPivot() const {
		return m_tPivot;
	}
	void SetPivot(const _SIZE& tPivot){
		m_tPivot = tPivot;
	}
	void SetPivot(float x,float y){
		m_tPivot.x = x;
		m_tPivot.y = y; 
	}
	void SetTag(wstring strTag) {
		m_strTag = std::move(strTag);
	}
	void SetPos(POSITION tPos) {
		m_tPos = std::move(tPos);
	}
	void SetPos(float x, float y) {
		m_tPos.x = x;
		m_tPos.y = y;
	}
	void SetPos(POINT tPos) {
		m_tPos = std::move(tPos);
	}

	void SetSize(_SIZE tSize) {
		m_tSize = std::move(tSize);
	}
	void SetSize(float x, float y) {
		m_tSize.x = x;
		m_tSize.y = y;
	}

	void SetTexture(class CTexture* pTexture);
	void SetTexture(const wstring& strKey,
		const wchar_t* pFileName = nullptr,
		const wstring& strPathKey = TEXTURE_PATH); 
public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CObj* Clone() = 0; 
public:
	template<typename T>
	static T* CreateObj(const wstring& strTag, class CLayer*
		pLayer = NULL) {
		T* pObj = new T;
		pObj->SetTag(strTag);
		if (!pObj->Init()) {
			SAFE_RELEASE(pObj);
			return NULL;
		}
		if (pLayer) {
			pLayer->AddObject(pObj);
		};
		AddObj(pObj); 
		//pObj->AddRef(); 
		return pObj;
	};
	
	static CObj* CreateCloneObj(const wstring& strTagPrototypeKey,
		const wstring& strTag,class CLayer* pLayer =nullptr);
	
};
