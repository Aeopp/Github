#include "Ref.h"

CRef::CRef() : m_iRef{ 1 } 
{
}

void CRef::AddRef() 
{
	++m_iRef;
}
