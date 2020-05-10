#pragma once
#include <memory>
#include <mutex>
// �Ķ���Ͱ� �ϳ��� ������ ���� �����η� �н�...
// �ƴ϶�� �ٷ� ȣ��
#define SUBCALL_RETURN(FuncName,Params) return sizeof...(Params) > 0 ?\
static_cast<_SubTy*>(this)->FuneName_Implementation(std::forward<ParamTys>(Params)...)\
	:\
	static_cast<_SubTy*>(this)->FuneName_Implementation();\

template<typename Management_Type>
struct manager_Interface/*manager_traits*/ {
protected : 
	manager_Interface() = default; 
	virtual ~manager_Interface() noexcept(true) = default;
public:
	// my manager Type
	using Type = Management_Type;
	using Super = manager_Interface<Management_Type>;

	friend class std::unique_ptr<manager_Interface>;
	friend struct std::unique_ptr<manager_Interface>::deleter_type;
	
	// CRTP
// ���̹� ��Ģ FuncName_Implementation(Pass...);
// TODO:: 2�ܰ� ��Ӻ��ʹ� ������ �۵� X 
	template<typename ...ParamTys>
	bool inline Init(ParamTys&&... Params)noexcept {
		return static_cast<Type*>(this)->Init_Implementation(std::forward<ParamTys>(Params)...); 
	}
	template<typename ...ParamTys>
	bool inline Clear(ParamTys&&... Params)noexcept {
		return static_cast<Type*>(this)->Clear_Implementation(std::forward<ParamTys>(Params)...); 
	}
	template<typename ...ParamTys>
	bool inline Frame(ParamTys&&... Params) {
		return static_cast<Type*>(this)->Frame_Implementation(std::forward<ParamTys>(Params)...);
	}
	template<typename ...ParamTys>
	bool inline Render(ParamTys&&... Params) {
		return static_cast<Type*>(this)->Render_Implementation(std::forward<ParamTys>(Params)...);
	}
};