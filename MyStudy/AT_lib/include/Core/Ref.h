#pragma once
#include "../Game.h"
class CRef
{
protected:
	CRef();
	virtual ~CRef() {};
protected:
	int m_iRef;
	bool m_bEnable;
	bool m_bLife;
public:
	void AddRef(); 
	int Release() {
		--m_iRef;
		if (m_iRef == 0) {
			delete this;
			return 0; 
		}
		return m_iRef; 
	}
	
	void SetEnable(bool bEnable) {
		m_bEnable = bEnable; 
	}
	void SetLife(bool bLife) {
		m_bLife = bLife; 
	}
	bool GetEnable() const {
		return m_bEnable; 
	}
	bool GetLife() const {
		return  m_bLife;
	}
	void Die()
	{
		m_bLife = false; 
	}
};

