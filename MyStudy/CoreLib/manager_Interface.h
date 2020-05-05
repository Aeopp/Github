#pragma once
#include <memory>
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
};