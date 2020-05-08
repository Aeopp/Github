#include "Input.h"
#include <windows.h>
#include "Util.h"

Input::~Input() noexcept(true)
{
	Clear();
}
bool Input::Init_Implementation()noexcept(false) 
{
	key_state.fill(EKey::None);
	return true;
};

bool Input::Frame_Implementation()
{
	// ���콺��ǥ�� ��ȯ�� Input �� ����Ѵ�. 
	world::CursorPosConversion();
	
	for (const auto& [_func, _KeyList, _Mappeds] : Func_Register)
	{
		for (auto& _Key : _KeyList)
		{
			// �ش�Ű�� ��� �������� �˻�
			auto Cur_Key = key_check(_Key);
			// �ش� Ű�� ���°� ����ڰ� ���ϴ� ��Ȳ�� �ϳ��� �´´ٸ� ȣ��
			if (Cur_Key == _Mappeds.first || Cur_Key == _Mappeds.second)
				_func();
		}
	};
	
	return true;
}; 

bool Input::Render_Implementation()
{
	return true;
}

bool Input::Clear_Implementation() noexcept
{
	func_clear();
	return true;
};

typename Input::EKey Input::key_check(input_type p_key) 
{
	const auto Cur_key = GetAsyncKeyState(p_key);
	// ���ȴٸ� �ֻ�����Ʈ�� ������ 1 
	// 10000000 0000000 �� And ���� ���� 0�� �ƴ϶��
	// Ű�� ������ ������
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
