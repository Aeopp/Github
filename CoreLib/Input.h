#pragma once
#include "manager_Interface.h"
#include <array>
#include <vector>
#include <functional>
#include <tuple>

class Input : public manager_Interface<Input>
{
public:
	enum class EKey :uint8_t {
		None = 0,
		Free,
		Press,
		Hold,
		Release,
	};
	
	//TODO :: Point ����ü ����
	//TODO :: ����Ʈ ����ü�� ���忡�� ����
	using input_type = uint32_t;
	using _InitInputList = std::initializer_list<input_type>;
	using _Mapped_Type = std::pair<typename Input::EKey, typename Input::EKey>;
	
	// ����ϴ� Ű�� �� Ű�ǻ��¸� �˷��ְ� �Լ��� ��Ͻ��ѳ�����
	// Ű�� Ű�ǻ��°� ��ġ�Ҷ� �Լ� ����
	using call_back_Ty = std::tuple<std::function<void()>, _InitInputList, _Mapped_Type>;

	Input& operator=(Input&&) = delete;
	Input& operator=(const Input&) = delete;
	Input(Input&&) = delete;
	Input(const Input&) = delete;
	virtual ~Input()noexcept(true) ;
	
	bool Frame_Implementation(); 
	bool Render_Implementation();
	bool Init_Implementation()noexcept(false) ;
	bool Clear_Implementation()noexcept ;


	// string ��ü ����� ��� ���۷����� �Ķ���� �ѱ��� ��������
	template<typename func_Ty, typename ... param_Tys>
	void  Func_Regist(std::initializer_list<input_type> InitInput,
		std::pair<typename Input::EKey, typename Input::EKey>
		Mapped_Keys, func_Ty&& Func, param_Tys&&... Params)&;
	
	template<typename param_Ty>
	bool delete_func(std::function<bool(const param_Ty&)>pred)noexcept;
	typename Input::EKey key_check(input_type p_key);
	void func_clear()& noexcept;
private:
	Input();

	std::vector<call_back_Ty> Func_Register;
	static inline constexpr size_t key_buffer_size = 256; 
	std::array<typename Input::EKey,key_buffer_size> key_state;

	friend class std::unique_ptr<Input>;
	friend struct std::unique_ptr<Input>::deleter_type;
	friend class util; 
};

template<typename func_Ty, typename ... param_Tys>
void  Input::Func_Regist(_InitInputList InitInput,
	_Mapped_Type Mapped_Keys,       func_Ty&& Func, param_Tys&&... Params )&
{
	auto&& binder = std::bind(std::forward<func_Ty>(Func),
	std::forward<param_Tys>(Params)...);
	
	Func_Register.emplace_back(binder, InitInput, Mapped_Keys);
};
