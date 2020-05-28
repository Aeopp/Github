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
	SCENE_CREATE m_eSceneType;

	static inline	  unordered_map<wstring, class CObj*> m_mapPrototype[SC_END];
public:
	void SetSceneType(SCENE_CREATE eType) {
		m_eSceneType = eType;  
	}
	SCENE_CREATE GetSceneType() {
		return m_eSceneType;
	}
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
	class CLayer* CreateLayer(const wstring& strTag, int iZOrder = 0);
	class CLayer* FindLayer(const wstring& strTag);

	static void ErasePrototype(
		SCENE_CREATE sc);
	 static void ErasePrototype(const wstring& strTag,
		 SCENE_CREATE sc);
	template<typename T>
	static T* CreateProtoType(const wstring& strTag,
		SCENE_CREATE sc) {
		T* pObj = new T;
		pObj->SetTag(strTag);
		if (!pObj->Init()) {
			SAFE_RELEASE(pObj);
			return NULL;
		}
		pObj->AddRef();
		m_mapPrototype[sc].insert(std::make_pair(strTag, pObj));
		//pObj->AddRef(); 
		return pObj;
	};
	static CObj* FindPtototype(const wstring& strKey,
		SCENE_CREATE sc);
	static  void ChangeProtoType(); 

	
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

