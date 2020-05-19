#pragma once
#include "../Game.h"
class CRef
{
protected:
	CRef();
	virtual ~CRef() {};
protected:
	int m_iRef;
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
};
