#pragma once
#include "TBitmap.h"
class TBitmapMgr : public TSingleton<TBitmapMgr>
{
	friend class TSingleton<TBitmapMgr>;
private:
	int						m_iCurIndex;
	std::map<int, TBitmap*>  m_Map;
	T_STR					m_csDefaultPath;
public:
	typedef std::map<int, TBitmap*>::iterator TItor;
	void    SetDefaultPath(T_STR szPath)
	{
		m_csDefaultPath = szPath;
	}
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		Load(HDC hScreenDC, T_STR szName);
	TBitmap* GetPtr(int iIndex);

private:
	TBitmapMgr();
public:
	~TBitmapMgr();
};

#define I_BitmapMgr TBitmapMgr::GetInstance()