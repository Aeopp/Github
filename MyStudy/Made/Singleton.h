#pragma once
#include <memory>_dbdao.h
#include <type_traits>
#include <mutex>__msvc_all_public_headers.hpp
#include "helper.h"
	// TODO :: Sub Ŭ���� Super Ŭ���� ������ �����������
	// TODO :: ������ ��� ����ϸ� �ȵ�
	// TODO :: private �⺻ ������ �Ҹ��� �����ϰ� �ݵ�� cpp�� ����
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