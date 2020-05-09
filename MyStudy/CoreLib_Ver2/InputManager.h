#pragma once
#include "Utility.h"
#include <array>
#include <limits>

class TInput : public SingleTon<TInput>
{
public :
	static constexpr inline uint32_t KeyMappedMaxSize = 256;
private:
	friend class SingleTon<TInput>;
	std::array<EKeyState,KeyMappedMaxSize> KeyStates;
	POINT		MousePosition;
public:
	bool		Frame();
	bool		Render();
	EKeyState	KeyCheck(uint32_t Key);
private:
	TInput();
public:
	~TInput();
};

#define GetInputManager TInput::Instance()