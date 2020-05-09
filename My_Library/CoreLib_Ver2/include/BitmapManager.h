#pragma once
#include "Bitmap.h"
class TBitmapMgr : public TSingleton<TBitmapMgr>
{
	friend class TSingleton<TBitmapMgr>;
private:
	int						m_iCurIndex;
	std::map<int, TBitmap*>  m_Map;
	tstring					m_csDefaultPath;
public:
	typedef std::map<int, TBitmap*>::iterator TItor;
	void    SetDefaultPath(tstring szPath)
	{
		m_csDefaultPath = szPath;
	}
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		Load(HDC hScreenDC, tstring szName);
	TBitmap* GetPtr(int iIndex);

private:
	TBitmapMgr();
public:
	~TBitmapMgr();
};

#define I_BitmapMgr TBitmapMgr::GetInstance()