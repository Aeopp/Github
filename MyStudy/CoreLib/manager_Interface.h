#pragma once
#include <memory>
template<typename Management_Type>
struct manager_Interface/*manager_traits*/ {
protected : 
	manager_Interface() = default; 
	virtual ~manager_Interface() noexcept(true) = default; 
public:
	using Type = Management_Type;
	friend class std::unique_ptr<manager_Interface>; 
	// �Ŵ������� �������̽��� �����ϱ� �����
	/*virtual bool clear()noexcept(true) = 0; 
	virtual bool Load() noexcept(true) = 0; */
};