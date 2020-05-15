#pragma once
#include <memory>_dbdao.h
#include <type_traits>
#include <mutex>__msvc_all_public_headers.hpp
// TODO :: Sub 클래스 Super 클래스 프렌드 지정해줘야함
// TODO :: 생성자 상속 사용하면 안됨
// TODO :: private 기본 생성자 소멸자 선언하고 반드시 cpp에 구현
// TODO :: SINGLETON_DECLARE(SubClass) DELETE_MOVE_COPY(Subclass) 
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


#define SINGLETON_DECLARE(Target)        \
private:\
	Target(){};\
	virtual ~Target()noexcept{};       \

#define DEFAULT_MOVE_COPY(Target)       \
public:\
Target(Target&&)noexcept = default;\
Target& operator=(Target&&)noexcept = default;\
Target(const Target&) = default;\
Target& operator=(const Target&) = default;\

// Singleton
// 이동 카피 삭제 
#define DELETE_MOVE_COPY(Manager)   \
public:\
Manager(Manager&&)noexcept = delete;\
Manager& operator=(Manager&&)noexcept = delete;\
Manager(const Manager&) = delete;\
Manager& operator=(const Manager&) = delete;\
