#include "Input.h"
#include <windows.h>
#include "Util.h"

Input::~Input() noexcept(true)
{
	Clear();
}
bool Input::Init()noexcept(false) 
{
	key_state.fill(EKey::None);
	return true;
};

bool Input::Frame()
{
	// 마우스좌표의 변환은 Input 이 담당한다. 
	world::CursorPosConversion();
	
	for (const auto& [_func, _KeyList, _Mappeds] : Func_Register)
	{
		for (auto& _Key : _KeyList)
		{
			// 해당키가 어떠한 상태인지 검사
			auto Cur_Key = key_check(_Key);
			// 해당 키의 상태가 사용자가 원하는 상황중 하나라도 맞는다면 호출
			if (Cur_Key == _Mappeds.first || Cur_Key == _Mappeds.second)
				_func();
		}
	};
	
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
};

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
	else 
		return false; 
}

void Input::func_clear() & noexcept
{
	Func_Register.clear();
	Func_Register.shrink_to_fit();
}

Input::Input()
{
	Init();
}
