#pragma once
#include "Utility.h"
#include <array>
#include <limits>

class InputManager : public SingleTon<InputManager>
{
public :
	static constexpr inline uint32_t KeyMappedMaxSize = 256;
private:
	friend class SingleTon<InputManager>;
	std::array<EKeyState,KeyMappedMaxSize> KeyStates;
	POINT		MousePosition;
public:
	bool		Frame();
	bool		Render();
	EKeyState	KeyCheck(uint32_t Key);
private:
	InputManager();
public:
	~InputManager()noexcept;
	DELETE_MOVE_COPY(InputManager)
};

#define GetInputManager InputManager::Instance()