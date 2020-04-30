#include "Input.h"
#include <Windows.h>

Input::~Input() noexcept(true)
{
	Clear(); 
}
bool Input::Init()
{
	return true;
}

bool Input::Frame()
{
	return true;
}

bool Input::Render() 
{
	for (const auto& [func, _Key, _KeyState] : Func_Register) 
		// 사용자가 원했던 Key == KeyState 상황
		if (key_check(_Key) == _KeyState) 
			func();


	return true;

}

bool Input::Clear() noexcept
{
	return true;
}

typename Input::EKey Input::key_check(input_type p_key) 
{
	auto Cur_key = GetAsyncKeyState(p_key);
	// 눌렸다면 최상위비트는 무조건 1 
	// 10000000 0000000 과 And 연산 이후 0이 아니라면
	// 키는 무조건 눌렸음
	if (Cur_key & 0x8000) {

		if (key_state[p_key] == EKey::Free ||
			key_state[p_key] == EKey::Release)

			key_state[p_key] = EKey::Press;

		else
			key_state[p_key] = EKey::Hold; 
	}
	else{
		if (key_state[p_key] == EKey::Press ||
			key_state[p_key] == EKey::Hold)

			key_state[p_key] = EKey::Release;

		else
			key_state[p_key] = EKey::Free; 
	}
	
	return key_state[p_key];
}



Input::Input()
{
	key_state.fill(EKey::None);
}
