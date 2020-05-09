#include "TTimer.h"
float	g_fSecondPerFrame = 0.0f;
float	g_fTimer = 0.0f;

bool	TTimer::Init()
{
	// 추가종속성 : winmm.lib 추가
	// 1000 -> 1초
	m_dwBeforeTick = timeGetTime();// 1/1000.0f 정밀도
	m_BeforeClock = TClock::now();
	return true;
}
bool	TTimer::Frame()
{
	//DWORD dwCurrentTick = timeGetTime();
	//DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	//m_fSecondPerFrame = dwElapseTick / 1000.0f;
	//m_fTimer += m_fSecondPerFrame;
	//m_dwBeforeTick = dwCurrentTick;


	//m_fFrameTime += m_fSecondPerFrame;
	//if (m_fFrameTime > 1.0f)
	//{		
	//	m_dwFPS = m_dwFrameCnt;
	//	m_dwFrameCnt = 0;
	//	m_fFrameTime = m_fFrameTime - 1.0f;
	//}
	//m_dwFrameCnt++;
	//m_dwBeforeTick = dwCurrentTick;


	TClock::time_point current= TClock::now();
	TMilliSeconds ElapseClock = std::chrono::duration_cast<TMilliSeconds>(current - m_BeforeClock);
	
	m_fSecondPerFrame = ElapseClock.count() / 1000.0f;
	m_fTimer += m_fSecondPerFrame;
	g_fSecondPerFrame = m_fSecondPerFrame;
	g_fTimer = m_fTimer;

	m_fFrameTime += m_fSecondPerFrame;
	if (m_fFrameTime > 1.0f)
	{
		m_dwFPS = m_dwFrameCnt;
		m_dwFrameCnt = 0;
		m_fFrameTime = m_fFrameTime - 1.0f;
	}
	m_dwFrameCnt++;

	m_BeforeClock = current;


	_stprintf_s(m_csBuffer,L"%10.4f:%d", 
	m_fTimer, m_dwFPS );
	return true;
}
bool	TTimer::Render()
{
	//std::cout << m_fTimer << ":" << m_dwFPS << std::endl;
	return true;
}
bool	TTimer::Release()
{
	return true;
}

TTimer::TTimer() 
{
	m_fSecondPerFrame = 0.0f;
	m_fTimer = 0.0f;
	m_fFrameTime = 0.0f;
	m_dwFrameCnt = 0;
	m_dwFPS = 0;
}
TTimer::~TTimer() {}
