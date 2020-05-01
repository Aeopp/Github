#include "Input.h"
#include <windows.h>

Input::~Input() noexcept(true)
{
	Clear(); 
}
bool Input::Init()noexcept(false) 
{
	return true;
};

bool Input::Frame()
{
	// 사용자가 원했던 Key == KeyState 상황일때 함수호출
	for (const auto& [func, _Key, _KeyState] : Func_Register)
		if (key_check(_Key) == _KeyState) 	func();

	return true;
}; 

bool Input::Render() 
{
	return true;
}

bool Input::Clear() noexcept
{
	func_clear();
	return true;
}

typename Input::EKey Input::key_check(input_type p_key) 
{
	const auto Cur_key = GetAsyncKeyState(p_key);
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

template<typename func_Ty>
bool Input::delete_func(std::function<bool(const func_Ty&)> pred) noexcept
{
	if (auto find_iter = std::find_if(std::begin(Func_Register), std::end(Func_Register), pred);

		find_iter != std::end(Func_Register))
	{
		Func_Register.erase(find_iter);
		return true;
	}
	else return false; 
}

void Input::func_clear() & noexcept
{
	Func_Register.clear();
	Func_Register.shrink_to_fit();
}

Input::Input()
{
	key_state.fill(EKey::None);
}
