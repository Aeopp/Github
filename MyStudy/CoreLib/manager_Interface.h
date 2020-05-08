#pragma once
#include <memory>
#include <mutex>
// 파라미터가 하나라도 있으면 실제 구현부로 패스...
// 아니라면 바로 호출
//#define SUBCALL_RETURN(FuncName,Params) return sizeof...(Params) > 0 ?\
//static_cast<_SubTy*>(this)->FuneName_Implementation(std::forward<ParamTys>(Params)...)\
//	:\
//	static_cast<_SubTy*>(this)->FuneName_Implementation();\

template<typename Management_Type>
struct manager_Interface/*manager_traits*/ {
protected:
	manager_Interface() = default;
	virtual ~manager_Interface() noexcept(true) = default;
public:
	// using Super::Super;
	manager_Interface& operator=(manager_Interface&&) = delete;
	manager_Interface& operator=(const manager_Interface&) = delete;
	manager_Interface(manager_Interface&&) = delete;
	manager_Interface(const manager_Interface&) = delete;

	// my manager Type
	using Type = Management_Type;
	using Super = manager_Interface<Management_Type>;

	friend class std::unique_ptr<manager_Interface>;
	friend struct std::unique_ptr<manager_Interface>::deleter_type;

//	// CRTP
//// 네이밍 규칙 FuncName_Implementation(Pass...);
//// TODO:: 2단계 상속부터는 다형성 작동 X 
	virtual bool Init()noexcept {
		return true;
	}
	virtual bool Clear()noexcept {
		return true;
	}
	virtual bool Frame() {
		return true;
	}
	virtual bool Render(){
		return true;
	}
};