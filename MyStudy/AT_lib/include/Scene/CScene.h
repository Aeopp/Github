#pragma once
#include "../Game.h"
class CScene
{
public:
	friend class CSceneManager;
protected:
	CScene();
protected:
	virtual ~CScene()noexcept;
protected:
	list<class CLayer*> m_LayerList; 
	static inline unordered_map<wstring,class CObj*> m_mapPrototype;
public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
	class CLayer* CreateLayer(const wstring& strTag, int iZOrder = 0);
	class CLayer* FindLayer(const wstring& strTag);

	static void ErasePrototype();
	static void ErasePrototype(const wstring& strTag);
	template<typename T>
	static T* CreateProtoType(const wstring& strTag) {
		T* pObj = new T;
		pObj->SetTag(strTag);
		if (!pObj->Init()) {
			SAFE_RELEASE(pObj);
			return NULL;
		}
		pObj->AddRef();
		m_mapPrototype.insert(std::make_pair(strTag, pObj));
		//pObj->AddRef(); 
		return pObj;
	};
	static CObj* FindPtototype(const wstring& strKey);
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

