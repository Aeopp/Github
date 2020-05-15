#pragma once
#include <memory>_dbdao.h
#include <type_traits>
#include <mutex>__msvc_all_public_headers.hpp
#include "helper.h"
template <class ManagerType>
class SingleTon
{
public:
	// TODO :: Sub Ŭ���� Super Ŭ���� ������ �����������
	// TODO :: ������ ��� ����ϸ� �ȵ�
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