#pragma once
#include <memory>_dbdao.h
#include <type_traits>
#include <mutex>__msvc_all_public_headers.hpp
#include "helper.h"
	// TODO :: Sub 클래스 Super 클래스 프렌드 지정해줘야함
	// TODO :: 생성자 상속 사용하면 안됨
	// TODO :: private 기본 생성자 소멸자 선언하고 반드시 cpp에 구현
	// TODO :: SINGLETON_DECLARE(SubClass) DELETE_MOVE_COPY(Subclass) "helper.h"
	// TODO :: friend class std::unique_ptr<SubClass>::deleter_type;
template <class ManagerType>
class SingleTon
{
public:
	template<typename...Types>
	static ManagerType& Instance(Types&&... params)
	{
		static std::unique_ptr<ManagerType> InstancePtr;
		static std::once_flag OnceFlag;
		std::call_once(OnceFlag, [](auto&&... params) {
			InstancePtr.reset(new ManagerType(std::forward<Types>(params)...)); },
			std::forward<Types>(params)...);
		return *(InstancePtr.get());
	};
protected:
	SingleTon() = default;
private:
	~SingleTon()noexcept = default;
	DELETE_MOVE_COPY(SingleTon)
};