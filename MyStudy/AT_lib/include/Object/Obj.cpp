#include "Obj.h"
#include "../Scene/CScene.h"
#include "../Scene/CSceneManager.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
#include "../Collision/Colinder.h"
#include "../CCore.h"
#include "../../CAnimation.h"
CObj::CObj() :
	m_pTexture{ nullptr },
	m_bIsPhysics{ false } ,
	m_fGravityTime(0.f),
	m_pAnimation{ nullptr}
{};

// Memory Leak Dected!! 
CObj::~CObj(){
	SAFE_RELEASE(m_pAnimation);
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pTexture);
 	/*SAFE_DELETE(m_pScene);
	SAFE_DELETE(m_pLayer); */
}
CObj::CObj(const CObj & Obj)
{
	*this = Obj;

	if (Obj.m_pAnimation) {
		m_pAnimation = Obj.m_pAnimation->Clone(); 
	}

	m_fGravityTime = 0.f; 

	if (m_pTexture) {
		m_pTexture->AddRef();
	}

	m_ColliderList.clear();
	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = Obj.m_ColliderList.end();
	for (iter = Obj.m_ColliderList.begin(); iter != iterEnd; ++iter) {
		CCollider* pColl = (*iter)->Clone();
		pColl->SetObj(this);
		m_ColliderList.push_back(pColl);
	}
	/*for (auto Object : Obj.m_CollinderList){
		auto* pCollider = Object->Clone();
		pCollider->SetObj(this);
		m_CollinderList.push_back(pCollider);
	}*/
}

void CObj::AddObj(CObj* pObj)
{
	pObj->AddRef(); 
	m_ObjList.push_back(pObj);
}

CObj* CObj::FindObject(const wstring& strTag)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end() ;

	for (iter = m_ObjList.begin(); iter != iterEnd;++iter) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;  
		}
	}
	return nullptr;
}

void CObj::EraseObj(CObj* pObj)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;){
		if (*iter == pObj) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter); 
			return; 
		}
		else
			++iter; 
	}
}

void CObj::EraseObj(const wstring& strTag)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;) {
		if ((*iter)->GetTag() == strTag) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
		else
			++iter;
	}
}

void CObj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

CAnimation* CObj::CreateAnimation(const wstring& strTag)
{
	SAFE_RELEASE(m_pAnimation);

	m_pAnimation = new CAnimation;
	m_pAnimation->SetTag(strTag);
	m_pAnimation->SetObj(this);

	if (!m_pAnimation->Init()) {
		SAFE_RELEASE(m_pAnimation);
		return nullptr;
	}

	m_pAnimation->AddRef();

	return m_pAnimation;
}
CCollider* CObj::GetCollider(const wstring& strTag)
{
	list<CCollider*>::iterator iter; 
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin();
		iter != iterEnd; ++iter) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;
		}
	}
	return nullptr;
}
bool CObj::AddAnimationClip(const wstring& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, const wstring& strTexKey, const wchar_t* pFileName, const wstring& strPathKey)
{
	if(!m_pAnimation)
	return false;

	m_pAnimation->AddClip(strName,
		eType, eOption,
		fAnimationLimitTime,
		iFrameMaxX,
		iFrameMaxY,
		iStartX, iStartY,
		iLengthX,
		iLengthY,
		fOptionLimitTime,
		strTexKey,
		pFileName, strPathKey);


	return true; 
}
bool CObj::AddAnimationClip(const wstring& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, const wstring& strTexKey, const vector<wstring>& vecFileName, const wstring& strPathKey)
{
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClip(strName,
		eType, eOption,
		fAnimationLimitTime,
		iFrameMaxX,
		iFrameMaxY,
		iStartX, iStartY,
		iLengthX,
		iLengthY,
		fOptionLimitTime,
		strTexKey,
		vecFileName, strPathKey);


	return true;
}
void CObj::SetAnimationClipColorkey(const wstring& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	if(m_pAnimation)
	m_pAnimation->SetClipColorkey(strClip, r, g, b);
}


void CObj::SetTexture(CTexture* pTexture){
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;
	if (pTexture)
		pTexture->AddRef();
}

void CObj::SetTexture(const wstring& strKey, const wchar_t* pFileName, const wstring& strPathKey){
		SAFE_RELEASE(m_pTexture);
		m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey,pFileName,strPathKey);
}

void CObj::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_pTexture->SetColorKey(r, g, b);
}

void CObj::Input(float fDeltaTime)
{
	for (auto iter = std::begin(m_ColliderList); iter != std::end(m_ColliderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
		}
		else ++iter;
	}
};

int CObj::Update(float fDeltaTime)
{
	
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter; 
			continue; 
		}

		(*iter)->Update(fDeltaTime);
		
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter; 
	}

	if (m_pAnimation) {
		m_pAnimation->Update(fDeltaTime);
	}
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	};

	for (auto iter = HitList.begin(); iter != std::end(HitList);) {
		if (iter->second == ECOLLISION_STATE::Release) {
			iter = HitList.erase(iter); 
		}
		else
			++iter;  
	}
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
	/*for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_CollinderList.erase(iter);
		}
		else ++iter;
	}*/

	//for (auto iter = std::begin(HitList); iter != std::end(HitList); ++iter) {
	//	if (iter->second == ECOLLISION_STATE::Nothing) {
	//		//SAFE_RELEASE(iter->first);
	//		HitList.erase(iter);
	//	}
	//}
	for (auto iter = std::begin(HitList); iter != std::end(HitList); ++iter) {
		auto Target = iter->first;
		auto State = FindHitList(iter->first);

		if (State.second != ECOLLISION_STATE::Keep &&
			State.second != ECOLLISION_STATE::First) {

			auto Test = Target->GetTag() + m_strTag.c_str();
			MessageBox(NULL, Test.c_str(), L"Release !! ", MB_OK);
		}
	}
};

void CObj::Hit(CObj* const Target, float fDeltaTime)
{
	if (m_strTag == L"Stage") {
		return;
	};

	if (auto Finditer = std::find_if(std::begin(HitList), std::end(HitList),
		[Target](decltype(HitList)::value_type value)
		{
			return Target == value.first;
		}); Finditer != std::end(HitList)) {

		if (Finditer->second == ECOLLISION_STATE::First) {

			Finditer->second = ECOLLISION_STATE::Keep;
		}
	}
	else {
		HitList.emplace_back(Target, ECOLLISION_STATE::First);
		FirstHitEvent(Target,fDeltaTime);
	}

	//if (State == std::end(HitList)) {
	//	AddHitList(Target,ECOLLISION_STATE::First);
	//}
	// 리스트에서 찾았다 충돌 유지중
	/*else if ((*State).second== ECOLLISION_STATE::First) {
		(*State).second = ECOLLISION_STATE::Keep;
	}*/
	//else {
	//	auto Test  = Target->GetTag() + m_strTag.c_str();
	//	
	//}


	//// 리스트에서 찾았다 충돌 유지중
	//else if (State.second == ECOLLISION_STATE::First ||
	//	State.second == ECOLLISION_STATE::Keep){

	//	State.second = ECOLLISION_STATE::Release;
	//}
}

void CObj::FirstHitEvent(CObj* const Target, float fDeltaTime)
{

}

void CObj::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	auto eraser = [Target](auto Pair) {return Pair.first == Target; };

	HitList.remove_if(eraser);
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture) {

		/*Rectangle(hDC, tPos.x, tPos.y, tPos.x + m_tSize.x, tPos.y + m_tSize.y);
		*/
		
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		POSITION tImagePos;

		if (m_pAnimation) {
			PANIMATIONCLIP pClip =
				m_pAnimation->GetCurrentClip();

			if (pClip->eType == AT_ATLAS) {
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
			
		}

		tImagePos += m_tImageOffset;

		if (m_pTexture->GetColorKeyEnable()==true) {
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x,
				m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y,
				m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else {
			BitBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y,
				SRCCOPY);
		}
	}

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->Render(hDC,fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
}

CObj* CObj::CreateCloneObj(const wstring& strTagPrototypeKey, const wstring& strTag, SCENE_CREATE sc,class CLayer* pLayer)
{
	  CObj* pProto = CScene::FindPtototype(strTagPrototypeKey, sc);

	if (!pProto)
		return nullptr;
	 
	CObj* pObj = pProto->Clone();
	pObj->SetTag(strTag);
	if (pLayer) {
		pLayer->AddObject(pObj); 
	}
	AddObj(pObj);
	return pObj;
}
