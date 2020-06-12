#include "Actor.h"
#include "Std.h"
#include "Mesh.h"
#include "World.h"
#include "Device.h"
#include "Math.h"

Actor::Actor() {};

Actor::~Actor()noexcept {};

void Actor::CreateMesh(ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext, 
	const std::wstring_view pTextureFileName,RECTANGLE rect) {

	_Mesh = std::make_shared<Mesh>();
	_Mesh->Create(pd3dDevice, pContext, pTextureFileName, rect,this);
};

bool Actor::Init() {
	if (IsValid(GetMesh())){
		GetMesh()->Init();
	}
	return true;
}
bool Actor::Release()noexcept {
	if (IsValid(GetMesh())) {
		GetMesh()->Release();
	}
	return true;
}
bool Actor::Frame(float DeltaTime) {
	if (IsValid(GetMesh())) {
		GetMesh()->Frame(DeltaTime);
	}
	return true;
}
bool Actor::Render(float DeltaTime) {
	if (IsValid(GetMesh())) {
		GetMesh()->Render(DeltaTime);
	}
	return true; 
}

