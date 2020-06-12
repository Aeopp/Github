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
	// ������ ��
	// T F
	Release,
	// ������ ���� ����
	// F F
	Free,
};

class Input : public SingleTon<Input> , public Interface_CallBack<Input>
{
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
	// ��Ƽ���� �̺�Ʈ , üŷ�� ���ϴ� Ű���� , üŷ�� ���ϴ� Ű�ε���
	void InputEventRegist_Implementation(std::function<void(float)> Event,
		EKeyState        KeyState, unsigned int KeyIndex) & noexcept;;
	// �̺�Ʈ �䱸������ �����Ѵٸ� �ݹ�
	void EventNotify(const float DeltaTime) & noexcept override;;
public:
inline 	POINT GetMousePosition() const& {
		return m_MousePos;
	}
	bool  Init();
	bool  Frame();
	bool  Release();
	DECLARE_SINGLETON(Input)
};