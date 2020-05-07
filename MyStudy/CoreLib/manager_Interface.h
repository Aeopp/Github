#pragma once
#include <memory>
#include <mutex>
// 파라미터가 하나라도 있으면 실제 구현부로 패스...
// 아니라면 바로 호출
#define SUBCALL_RETURN(FuncName,Params) return sizeof...(Params) > 0 ?\
static_cast<_SubTy*>(this)->FuneName_Implementation(std::forward<ParamTys>(Params)...)\
	:\
	static_cast<_SubTy*>(this)->FuneName_Implementation();\

template<typename Management_Type>
struct manager_Interface/*manager_traits*/ {
protected : 
	manager_Interface() = default; 
	virtual ~manager_Interface() noexcept(true) = default;

	// 이함수로 싱글턴 생성한다면 util 헬퍼함수는 사용하면 안됨
	//template<typename ... ParamTypes>
	//static constexpr inline Management_Type& GetInstance(ParamTypes... Params)
	//{
	//	static std::once_flag Flag;
	//	static Management_Type* _Manager;
	//	// 스레드 개수와 상관없이 단 한번의 실행만 한다
	//	
	//	std::call_once(Flag, [](auto&&... Params)
	//		{
	//			_Manager =  new Management_Type(std::forward<ParamTypes>(Params)...);
	//		});
	//	
	//
	//	return _Manager;
	//};
	
public:
	// my manager Type
	using Type = Management_Type;
	using Super = manager_Interface<Management_Type>;

	friend class std::unique_ptr<manager_Interface>;
	friend struct std::unique_ptr<manager_Interface>::deleter_type;
	
	// CRTP
// 네이밍 규칙 FuncName_Implementation(Pass...);
// TODO:: 2단계 상속부터는 다형성 작동 X 
	template<typename ...ParamTys>
	bool inline Init(ParamTys&&... Params)noexcept {
		return sizeof...(Params) > 0 ? 
			static_cast<Type*>(this)->Init_Implementation(std::forward<ParamTys>(Params)...)
			:
			static_cast<Type*>(this)->Init_Implementation();
	}
	template<typename ...ParamTys>
	bool inline Clear(ParamTys&&... Params)noexcept {
		return sizeof...(Params) > 0 ?
			static_cast<Type*>(this)->Clear_Implementation(std::forward<ParamTys>(Params)...)
			:
			static_cast<Type*>(this)->Clear_Implementation();
	}
	template<typename ...ParamTys>
	bool inline Frame(ParamTys&&... Params) {
		return sizeof...(Params) > 0 ?
			static_cast<Type*>(this)->Frame_Implementation(std::forward<ParamTys>(Params)...)
			:
			static_cast<Type*>(this)->Frame_Implementation();
	}
	template<typename ...ParamTys>
	bool inline Render(ParamTys&&... Params) {
		return sizeof...(Params) > 0 ?
			static_cast<Type*>(this)->Render_Implementation(std::forward<ParamTys>(Params)...)
			:
			static_cast<Type*>(this)->Render_Implementation();
	}
};