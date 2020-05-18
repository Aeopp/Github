#pragma once
#include "../Game.h"
#include "../Types.h"
class CObj
{
protected:
	CObj();
	virtual ~CObj() = 0;
protected:
	int m_iRef; 
	string m_strTag;
	POSITION m_tPos;
	_SIZE m_tSize;
public:
	



	void AddRef() {
		++m_iRef;
	}
	int Release() {
		--m_iRef;
		if (m_iRef == 0) {
			delete this; 
			return 0; 
		}
		return m_iRef; 
	}
	string GetTag()const {
		return m_strTag ;  
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
	void SetSize(float x, float y ) {
		m_tSize.x = x;
		m_tSize.y = y;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};