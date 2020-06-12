#include "Timer.h"

// ��Ƽ���� �̺�Ʈ , üŷ�� ���ϴ� Ű���� , üŷ�� ���ϴ� Ű�ε���
 void Timer::InputEventRegist_Implementation(std::function<void(float)> Event, ECategory TimerState, float EventTime) & noexcept {
	TimerEventTable.emplace_back(std::move(Event), std::move(TimerState),
		std::move(EventTime), std::move(EventTime));
}
 // �̺�Ʈ �䱸������ �����Ѵٸ� �ݹ�
  void Timer::EventNotify(const float DeltaTime) & noexcept {
	 for (auto iter = std::begin(TimerEventTable); iter != std::end(TimerEventTable);) {
		 auto& [Event, TimerState, CurrentRemainTime, EventTime] = *iter;
		 CurrentRemainTime -= DeltaTime;

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
 }



bool	Timer::Init()
{
	// �߰����Ӽ� : winmm.lib �߰�
	// 1000 -> 1��
	m_dwBeforeTick = timeGetTime();// 1/1000.0f ���е�
	m_BeforeClock = TClock::now();
	return true;
}
bool	Timer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecondPerFrame = dwElapseTick / 1000.0f;
	m_fTimer += m_fSecondPerFrame;
	m_dwBeforeTick = dwCurrentTick;

	m_fFrameTime += m_fSecondPerFrame;
	if (m_fFrameTime > 1.0f)
	{
		m_dwFPS = m_dwFrameCnt;
		m_dwFrameCnt = 0;
		m_fFrameTime = m_fFrameTime - 1.0f;
	}
	m_dwFrameCnt++;
	m_dwBeforeTick = dwCurrentTick;

	EventNotify(GetDeltaTime());

	return true;
}
bool	Timer::Render()
{
	return true;
}
bool	Timer::Release()
{
	return true;
}


Timer::Timer() {
	
}
Timer::~Timer() noexcept {
}

