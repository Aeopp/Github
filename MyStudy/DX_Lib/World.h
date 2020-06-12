#pragma once
<<<<<<< HEAD
#include "Std.h"
class World : public SingleTon<World> 
{
public:
	template<typename ActorType>
	void CreateActor();
	template<typename ActorType>
	void AddActor(std::shared_ptr< ActorType> TargetActor) & noexcept;
	void EraseActor(const std::wstring_view& MatchTag) & noexcept;
private:
	std::vector<std::shared_ptr<class Object>> ObjectTable;
	std::vector<std::shared_ptr<class Actor>> ActorTable;
public:
	bool Init();
	bool Release()noexcept;
	bool Frame(float DeltaTime);
	bool Render(float DeltaTime);

	DECLARE_SINGLETON(World)
};

template<typename ActorType>
void World::CreateActor()
{
	static_assert(std::is_base_of_v < Actor, ActorType >&& "");

	// ���⼭ ��ü ���� Ǫ��
	AddActor(std::make_shared<ActorType>() );
};
template<typename ActorType>
void World::AddActor(std::shared_ptr< ActorType> TargetActor) & noexcept {
	static_assert(std::is_base_of_v < Actor, ActorType > && "");

	ActorTable.push_back(TargetActor);
}
=======

class World
{

};

>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
