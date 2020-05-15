#pragma once
#include <memory>_dbdao.h
#include <type_traits>
#include <mutex>__msvc_all_public_headers.hpp
#include "helper.h"
template <class ManagerType>
class SingleTon
{
public:
	// TODO :: Sub 클래스 Super 클래스 프렌드 지정해줘야함
	// TODO :: 생성자 상속 사용하면 안됨
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