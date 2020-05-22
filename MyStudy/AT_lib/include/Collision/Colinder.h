#pragma once
#include "../Core/Ref.h"
using namespace std::placeholders;

class CColinder : 
	 public CRef
{
protected:
	friend class CObj;
public :
	CColinder();
	CColinder(const CColinder& coll);
	virtual ~CColinder()noexcept = 0;
	using Funclist_Ty = list<function<void(CColinder*, CColinder*, float)>>;
protected:
	COLLIDER_TYPE m_eCollType;
	class CObj* m_pObj;
	list<CColinder*> m_CollisionList; 
	// �浹 ó�� �޼ҵ� �������̽� �浹ü,�浹ü,float
	list<function<void(CColinder*, CColinder*, float)>> m_FuncList[CS_END];
	POSITION m_tPrevPos; 
public :
	void AddCollisionFunction(COLLISION_STATE eState,
		void (*pFunc)(CColinder*, CColinder*, float)) {

		function<void(CColinder*, CColinder*, float)> func;
		func = bind(pFunc, _1, _2, _3);

		m_FuncList[eState].push_back(func);
	}
	template<typename T>
	void AddCollisionFunction(COLLISION_STATE eState,T* pObj,
		void (T::*pFunc)(CColinder*, CColinder*, float)) {

		function<void(CColinder*, CColinder*, float)> func;
		func = bind(pFunc, pObj, _1, _2, _3 );

		m_FuncList[eState].push_back(func);
	}
	void CallFunction(COLLISION_STATE eState,
		CColinder* pDest,float fDeltaTime) {

		Funclist_Ty::iterator iterEnd = m_FuncList[eState].end();

		for (auto iter = m_FuncList[eState].begin(); iter != iterEnd; ++iter) {
			(*iter)(this, pDest, fDeltaTime);
		}
	}
public:
	void AddCollider(CColinder* pCollider) {
		m_CollisionList.push_back(pCollider);
	}
	// �̹� �浹 ������ �����ϴ� ��ƾ
	// TODO :: �̷��� �ϴ°�... ������??  
	bool CheckCollisionList(CColinder* pCollider) {
		list<CColinder*>::iterator iter;
		list<CColinder*>::iterator iterEnd = m_CollisionList.end();
		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
			if (*iter == pCollider) {
				return true; 
			}
		}
		return false; 
	}
	void EraseCollisionList(CColinder* pCollider) {
	/*	m_CollisionList.remove_if([pCollider]
		(auto Target) { return Target == pCollider; });*/

		list<CColinder*>::iterator iter;
		list<CColinder*>::iterator iterEnd = m_CollisionList.end();
		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
			if (*iter == pCollider) {
				m_CollisionList.erase(iter); 
				break;
			}
		}
	}
	COLLIDER_TYPE GetColliderType()const {
		return m_eCollType;
	}
	class CObj* GetObj()const {
		return m_pObj;
	}
	void SetObj(class CObj* pObj) {
		m_pObj = pObj;
	}
public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual bool Collision(CColinder* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColinder* Clone() = 0;

protected:
	bool CollisionRectToRect(const RECTANGLE& src,
		const RECTANGLE& dest);
};

