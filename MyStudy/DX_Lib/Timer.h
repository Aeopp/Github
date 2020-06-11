#pragma once
#include "Std.h"
#include "CallBackInterface.h"
#include <chrono>

class Timer : public Interface_CallBack<Timer> 
{
public:
	enum class ECategory : uint8_t {
		Loop,
		Once,
	};
	std::wstring		m_csName;
	TCHAR		m_csBuffer[MAX_PATH];
	float		m_fSecondPerFrame;
	float		m_fTimer;
	float		m_fFrameTime;
	DWORD		m_dwBeforeTick;
	DWORD		m_dwFrameCnt;
	int			m_dwFPS;
	std::vector<std::tuple<std::function<void(float)>, ECategory, float,float>> TimerEventTable;
public :
	// ��Ƽ���� �̺�Ʈ , üŷ�� ���ϴ� Ű���� , üŷ�� ���ϴ� Ű�ε���
	void InputEventRegist_Implementation(std::function<void(float)> Event,
		ECategory    TimerState, float EventTime) & noexcept;;
	// �̺�Ʈ �䱸������ �����Ѵٸ� �ݹ�
	void EventNotify(const float DeltaTime) & noexcept override;;
public:
	typedef std::chrono::high_resolution_clock	TClock;
	typedef std::chrono::milliseconds			TMilliSeconds;
	TClock::time_point m_BeforeClock;
public:
	virtual bool	Init();		// �ʱ�ȭ
	virtual bool	Frame();	// ���
	virtual bool	Render();	// ��ο�
	virtual bool	Release();	// �Ҹ�
public:
	Timer();
	virtual ~Timer();
};


