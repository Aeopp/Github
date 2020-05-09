#pragma once
#include "TBaseObject.h"
#include <chrono>
class TTimer : public TBaseObject
{
public:
	T_STR		m_csName;
	TCHAR		m_csBuffer[MAX_PATH];
	float		m_fSecondPerFrame;
	float		m_fTimer;
	float		m_fFrameTime;
	DWORD		m_dwBeforeTick;
	DWORD		m_dwFrameCnt;
	int			m_dwFPS;

public:
	typedef std::chrono::high_resolution_clock	TClock;
	typedef std::chrono::milliseconds			TMilliSeconds;
	TClock::time_point m_BeforeClock;
public:
	virtual bool	Init()	override;		// 초기화
	virtual bool	Frame()	override;	// 계산
	virtual bool	Render()	override;	// 드로우
	virtual bool	Release()	override;	// 소멸
public:
	TTimer();
	virtual ~TTimer();
};


