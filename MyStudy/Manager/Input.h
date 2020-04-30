#include "manager_Interface.h"
#include <array>
#include <vector>
#include <functional>
#include <tuple>
#pragma once

class Input : private manager_Interface<Input>
{
public:
	using input_type = uint32_t;

	enum class EKey :uint8_t {
		None = 0,
		Free,
		Press,
		Hold,
		Release,
	};
	// 희망하는 키와 그 키의상태를 알려주고 함수를 등록시켜놓으면
	// 키와 키의상태가 일치할때 함수 실행
	using call_back_Ty = std::tuple<std::function<void()>,
	input_type, typename Input::EKey>;

	Input& operator=(Input&&) = delete;
	Input& operator=(const Input&) = delete;
	Input(Input&&) = delete;
	Input(const Input&) = delete;
	virtual ~Input()noexcept(true) ;

	bool Init(); 
	bool Frame(); 
	bool Render(); 
	bool Clear()noexcept; 
	
	void inline Func_Regist(std::function<void()> P_Func,
				input_type P_Input, typename Input::EKey P_KeyState)&;
private:
	Input();

	typename Input::EKey key_check(input_type p_key);

	std::vector<call_back_Ty> Func_Register;
	static inline constexpr size_t key_buffer_size = 256; 
	std::array<typename Input::EKey,key_buffer_size> key_state;

	friend class std::unique_ptr<Input>;
	friend struct std::unique_ptr<Input>::deleter_type;
	friend class util; 
};

inline void Input::Func_Regist(std::function<void()> P_Func,
	input_type P_Input, typename Input::EKey P_KeyState)&
{
	Func_Register.emplace_back(P_Func,P_Input,P_KeyState);
}