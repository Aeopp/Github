#pragma once
#include "Std.h"
#include <array>
#include <dinput.h>
#include <sstream>
#include <functional>
#include <tuple>

#include "CallBackInterface.h"
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

enum class EKeyState : uint8_t {
	// F T
	Press,
	// T T
	Hold,
	// 눌렀다 뗌
	// T F
	Release,
	// 눌려진 적이 없음
	// F F
	Free,
};

class Input : public Singleton<Input> , public Interface_CallBack<Input>
{
	friend class Singleton<Input>;
public:
	LPDIRECTINPUT8 m_pDI;
	LPDIRECTINPUTDEVICE8  m_pKey;
	LPDIRECTINPUTDEVICE8  m_pMouse;
	static constexpr unsigned int KeyNumber = 256; 
	BYTE		 m_KeyState[KeyNumber];
	BYTE         m_OldKeyState[KeyNumber];
	std::array<EKeyState, KeyNumber> CurrentKeyState;

	std::vector < std::tuple<std::function<void(float)>, EKeyState, unsigned int>> InputEventTable; 
	DIMOUSESTATE m_MouseState;
	POINT		 m_MousePos;
public :
	 EKeyState GetCurrentTargetKeyState(unsigned int TargetKeyIdx)const&;;
	// 노티파이 이벤트 , 체킹을 원하는 키상태 , 체킹을 원하는 키인덱스
	void InputEventRegist_Implementation(std::function<void(float)> Event,
		EKeyState        KeyState, unsigned int KeyIndex) & noexcept;;
	// 이벤트 요구조건을 충족한다면 콜백
	void EventNotify(const float DeltaTime) & noexcept override;;
public:
	bool  Init();
	bool  Frame();
	bool  Release();
private:
	Input();
public:
	~Input() {}
};

#define I_Input Input::GetInstance()