#pragma once
#include "../Core/Ref.h"
#include "../Types.h"
#include "../Scene/Layer.h"
class CObj : public CRef
{
protected:
	CObj();
	virtual ~CObj();
	CObj(const CObj& Obj);
protected:
	int m_iRef;
	string m_strTag;
	POSITION m_tPos;
	_SIZE m_tSize;
	POSITION m_tPivot;
	class CScene* m_pScene;
	class CLayer* m_pLayer;
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
	string GetTag()const {
		return m_strTag;
	}
	POSITION GetPos()const {
		return m_tPos;
	}
	_SIZE GetSize()const {
		return m_tSize;
	};
public:
	void SetTag(string strTag) {
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
		m_tPos = std::move(tSize);
	}
	void SetSize(float x, float y) {
		m_tSize.x = x;
		m_tSize.y = y;
	}
public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
public:
	template<typename T>
	static T* CreateObj(const string& strTag, class CLayer*
		pLayer = NULL) {
		T* pObj = new T;
		if (!pObj->Init()) {
			SAFE_RELEASE(pObj);
			return NULL;
		}
		if (pLayer) {
			pLayer->AddObject(pObj);
		};
		//pObj->AddRef(); 
		return pObj;
	};
};
