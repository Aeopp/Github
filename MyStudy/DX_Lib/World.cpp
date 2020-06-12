#include "World.h"
<<<<<<< HEAD
#include "Object.h"
#include "Actor.h"

World::~World()noexcept {};
World::World() {};

 void World::EraseActor(const std::wstring_view& MatchTag) & noexcept {
	 if (auto iter = std::find_if(std::begin(ActorTable), std::end(ActorTable), [&MatchTag]
	 (auto Actor) {return Actor->GetTag() == MatchTag;  }); iter != std::end(ActorTable)) {
		 ActorTable.erase(iter);
	 }
 }

bool World::Init()
{
	return true;
}

bool World::Release() noexcept
{
	return true;
}

bool World::Frame(float DeltaTime)
{
	for (auto& Actor : ActorTable) {
		if(IsValid(Actor) ){
			Actor->Frame(DeltaTime);
		}
	}
	return true;
}

bool World::Render(float DeltaTime)
{
	for (auto& Actor : ActorTable) {
		if (IsValid(Actor)) {
			Actor->Render(DeltaTime);
		}
	}
	return true;
}
=======
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
