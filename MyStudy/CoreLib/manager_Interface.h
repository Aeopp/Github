#pragma once
#include <memory>
#include <mutex>
// �Ķ���Ͱ� �ϳ��� ������ ���� �����η� �н�...
// �ƴ϶�� �ٷ� ȣ��
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
//// ���̹� ��Ģ FuncName_Implementation(Pass...);
//// TODO:: 2�ܰ� ��Ӻ��ʹ� ������ �۵� X 
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