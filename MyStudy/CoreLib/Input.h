#pragma once
#include "manager_Interface.h"
#include <array>
#include <vector>
#include <functional>
#include <tuple>

class Input : private manager_Interface<Input>
{
public:
	Point ����ü ����
	����Ʈ ����ü�� ���忡�� ����
	using input_type = uint32_t;

	enum class EKey :uint8_t {
		None = 0,
		Free,
		Press,
		Hold,
		Release,
	};
	// ����ϴ� Ű�� �� Ű�ǻ��¸� �˷��ְ� �Լ��� ��Ͻ��ѳ�����
	// Ű�� Ű�ǻ��°� ��ġ�Ҷ� �Լ� ����
	using call_back_Ty = std::tuple<std::function<void()>,
	input_type, typename Input::EKey>;

	Input& operator=(Input&&) = delete;
	Input& operator=(const Input&) = delete;
	Input(Input&&) = delete;
	Input(const Input&) = delete;
	virtual ~Input()noexcept(true) ;
	
	virtual bool Frame(); 
	virtual bool Render();
	virtual bool Init()noexcept(false) ;
	virtual bool Clear()noexcept ;


	// string ��ü ����� ��� ���۷����� �Ķ���� �ѱ��� ��������
	template<typename func_Ty,typename ... param_Tys>
	void inline Func_Regist(const input_type P_Input, const typename Input::EKey P_KeyState,func_Ty&& Func, param_Tys&&... Params)&;
	
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
void inline Input::Func_Regist(const input_type P_Input, const typename Input::EKey P_KeyState,func_Ty&& Func, param_Tys&&... Params )&
{
	auto&& binder = std::bind(std::forward<func_Ty>(Func),
	std::forward<param_Tys>(Params)...);
	
	Func_Register.emplace_back(binder, P_Input, P_KeyState);
};
