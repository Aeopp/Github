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
public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
	class CLayer* CreateLayer(const string& strTag, int iZOrder = 0);
	
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

