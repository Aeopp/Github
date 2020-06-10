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
	T_STR		m_csName;
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
		ECategory    TimerState, float EventTime) & noexcept {
		TimerEventTable.emplace_back(std::move(Event), std::move(TimerState),
			std::move(EventTime), std::move(EventTime));
	};
	// �̺�Ʈ �䱸������ �����Ѵٸ� �ݹ�
	void EventNotify(const float DeltaTime)& noexcept override {
		for (auto iter = std::begin(TimerEventTable); iter != std::end(TimerEventTable);) {
			auto& [Event, TimerState, CurrentRemainTime, EventTime] =  *iter; 
			CurrentRemainTime -=  DeltaTime;

			if (CurrentRemainTime < 0) {
				Event(DeltaTime);
				if (TimerState == Timer::ECategory::Once) {
					iter = TimerEventTable.erase(iter);  
					continue; 
				}
				else if (TimerState == Timer::ECategory::Loop) {
					CurrentRemainTime = CurrentRemainTime + EventTime;
				}
			}
			++iter;  
		}
	};
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


