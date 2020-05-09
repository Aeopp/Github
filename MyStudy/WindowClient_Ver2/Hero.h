#pragma once
#include "Actor.h"
class THeroObj : public TObject
{
public:
	float	m_fSpeed;
public:
	bool	Frame();
public:
	THeroObj();
	virtual ~THeroObj();
};

