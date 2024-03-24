#include "RootObject.h"
#include "SceneManager.h"


RootObject::RootObject(GameObject* parent):
	GameObject(parent, "RootObject")
{
}


RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	Instantiate<SceneManager>(this);
}

void RootObject::Update(const float&dt)
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}
