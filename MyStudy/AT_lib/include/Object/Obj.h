#pragma once
#include "../Core/Ref.h"
#include "../Types.h"
#include "../Scene/Layer.h"
#include "../Core/Camera.h"
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
	list<class CCollider*> m_ColliderList;
	class CScene* m_pScene;
	class CLayer* m_pLayer;
	class CTexture* m_pTexture;
	list<std::pair<class CObj*,ECOLLISION_STATE>> HitList;
public:
	/*inline void SetHitList(class CObj* ObjKey,ECOLLISION_STATE NewEState)& {
		auto is_find = std::find_if(HitList.begin(), HitList.end(),
			[&ObjKey](auto Pair) {if (Pair.first == ObjKey) return true; else return false; });

		if (is_find != std::end(HitList)) {
			is_find->second = NewEState; 
		}
	}*/
	inline list<std::pair<class CObj*, ECOLLISION_STATE>>& GetHitList()& noexcept{
		return HitList;
	}
	inline void AddHitList(class CObj* Obj,
		ECOLLISION_STATE ESTATE)& {
		HitList.push_back(pair{ Obj,ESTATE });
	}
	inline void EraseHitList(class CObj* Obj)& {

	/*	HitList.remove_if([Obj](auto Pair) {
			if (Pair.first == Obj)return true;
			});*/

		/*auto is_find = std::find_if(std::begin(HitList), std::end(HitList), [Obj](auto Pair) {
			if (Pair.first == Obj)return true;
			}           );

		if (is_find != std::end(HitList)) {
			SAFE_RELEASE(is_find->first);
			HitList.erase(is_find);
		}*/
	
	}
	inline std::pair<class CObj*, ECOLLISION_STATE> FindHitList(class CObj* Obj) {
		auto is_find = std::find_if(std::begin(HitList), std::end(HitList),
			[Obj](auto Pair) {
				if (Pair.first == Obj)return true;
			});

		if (is_find != std::end(HitList)) {
			return *is_find;
		}
		else {
			return {nullptr,ECOLLISION_STATE::Nothing};
		}
	}
	/* list<class CCollider*>* GetColliderList() {
		return &m_ColliderList;
	}*/
	POSITION GetCollisionPos()const {
		auto Pos = GetPos();
		auto Size = GetSize();
		auto Pivot = GetPivot();

		POSITION tPos = Pos - Size * Pivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();
		return tPos; 
	}
	RECTANGLE GetCollisionRect()const {
		auto Pos = GetCollisionPos();
		return RECTANGLE{ Pos.x, Pos.y, Pos.x + m_tSize.x, Pos.y + m_tSize.y };
	}
	const list<class CCollider*>* GetColliderList()const {
		return &m_ColliderList;
	}
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
	virtual void Hit(CObj* const Target, float fDeltaTime); 
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

	// 충돌 메소드 필드
	template<typename T>
	T* AddCollider(const wstring& strTag){
		T* pCollider = new T;
		pCollider->SetObj(this);
		
		if (!pCollider->Init()) {
			SAFE_RELEASE(pCollider);
			return NULL;
		}
		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);
		return pCollider;
	}

	bool CheckCollider(){
		return !m_ColliderList.empty(); 
	}
};
