#pragma once
#include "../Game.h"
class CLayer
{
private:
	friend class CScene; 
private: 
	CLayer();
private:
	class CScene* m_pScene; 
	string m_strTag; 
	int m_iZOrder; 
	list<class CObj*> m_ObjList;
public :
	~CLayer();
public:
	void Input(float fDeltaTime);
	int  Update(float fDeltaTime);
	int  LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
	void AddObject(class CObj* pObj); 
	void SetTag(const string& strTag) {
		m_strTag = strTag;
	}
	void SetZOrder(int iZOrder) {
		m_iZOrder = iZOrder; 
	}
	int GetZOrder()const {
		return m_iZOrder; 
	}
	string GetTag()const {
		return m_strTag;
	}
	void SetScene(class CScene* pScene) {
		m_pScene = pScene; 
	}
	CScene* GetScene() const {
		return m_pScene; 
	}
};

