#pragma once
#include "TSound.h"
class TSoundMgr : public TSingleton<TSoundMgr>
{
	friend class TSingleton<TSoundMgr>;
private:
	int						m_iCurIndex;
	std::map<int, TSound*>  m_Map;
	FMOD::System*			m_pSystem;
	T_STR					m_csDefaultPath;
public:
	typedef std::map<int, TSound*>::iterator TItor;
	//// Singleton
	//static TSoundMgr& GetInstance()
	//{
	//	static TSoundMgr mgr;
	//	return mgr;
	//}
	void    SetDefaultPath(T_STR szPath)
	{
		m_csDefaultPath = szPath;
	}
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		Load(T_STR szName);
	TSound* GetPtr(int iIndex);
	
private:
	TSoundMgr();
public:
	~TSoundMgr();
};

#define I_SoundMgr TSoundMgr::GetInstance()