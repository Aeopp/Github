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
	// 노티파이 이벤트 , 체킹을 원하는 키상태 , 체킹을 원하는 키인덱스
	void InputEventRegist_Implementation(std::function<void(float)> Event,
		ECategory    TimerState, float EventTime) & noexcept {
		TimerEventTable.emplace_back(std::move(Event), std::move(TimerState),
			std::move(EventTime), std::move(EventTime));
	};
	// 이벤트 요구조건을 충족한다면 콜백
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
	virtual bool	Init();		// 초기화
	virtual bool	Frame();	// 계산
	virtual bool	Render();	// 드로우
	virtual bool	Release();	// 소멸
public:
	Timer();
	virtual ~Timer();
};


