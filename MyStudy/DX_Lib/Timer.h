#pragma once
#include "Std.h"
#include "CallBackInterface.h"
#include <chrono>

class Timer : public SingleTon<Timer> ,public Interface_CallBack<Timer> 
{
public:
	enum class ECategory : uint8_t {
		Loop,
		Once,
	};
<<<<<<< HEAD
	std::wstring		m_csName{};
	std::wstring m_csBuffer;
	float		m_fSecondPerFrame{ 0 };
	float		m_fTimer{ 0 };;
	float		m_fFrameTime{ 0 };;
	DWORD		m_dwBeforeTick{ 0 };;
	DWORD		m_dwFrameCnt{ 0 };;
	int			m_dwFPS{ 0 };;
	float TimeScale  { 1.f } ;
=======
	std::wstring		m_csName;
	TCHAR		m_csBuffer[MAX_PATH];
	float		m_fSecondPerFrame;
	float		m_fTimer;
	float		m_fFrameTime;
	DWORD		m_dwBeforeTick;
	DWORD		m_dwFrameCnt;
	int			m_dwFPS;
>>>>>>> parent of 7fb459c... Revert "í…ìŠ¤ì²˜ ì´ë¯¸ì§€ ë„ìš°ëŠ”ë°ê¹Œì§€ êµ¬í˜„"
	std::vector<std::tuple<std::function<void(float)>, ECategory, float,float>> TimerEventTable;
public :
	// ³ëÆ¼ÆÄÀÌ ÀÌº¥Æ® , Ã¼Å·À» ¿øÇÏ´Â Å°»óÅÂ , Ã¼Å·À» ¿øÇÏ´Â Å°ÀÎµ¦½º
	void InputEventRegist_Implementation(std::function<void(float)> Event,
		ECategory    TimerState, float EventTime) & noexcept;;
	// ÀÌº¥Æ® ¿ä±¸Á¶°ÇÀ» ÃæÁ·ÇÑ´Ù¸é Äİ¹é
	void EventNotify(const float DeltaTime) & noexcept override;
	inline void SetTimeScale(const float ScaleValue) & noexcept;
	inline float GetDeltaTime() const& noexcept;
	inline float GetCurrentTime() const& noexcept;

public:
	typedef std::chrono::high_resolution_clock	TClock;
	typedef std::chrono::milliseconds			TMilliSeconds;
	TClock::time_point m_BeforeClock;
public:
	virtual bool	Init();		// ÃÊ±âÈ­
	virtual bool	Frame();	// °è»ê
	virtual bool	Render();	// µå·Î¿ì
	virtual bool	Release();	// ¼Ò¸ê
public:
	DECLARE_SINGLETON(Timer)
};
inline float Timer::GetCurrentTime() const& noexcept {
	return m_fTimer;
}

inline void Timer::SetTimeScale(const float ScaleValue) & noexcept {
	TimeScale = ScaleValue;
}

inline float Timer::GetDeltaTime() const& noexcept {
	return m_fSecondPerFrame * TimeScale;
}