#include "ModeratorSequence.h"
#include"EnemyManager.h"
ModeratorSequence::ModeratorSequence(GameObject* parent):GameObject(parent,"ModeratorSequence")
{
	curTime = 0;
	ttlTime = 0;
	waves = 0;
	manager = nullptr;
}

ModeratorSequence::~ModeratorSequence()
{
	Release();
}

void ModeratorSequence::Initialize()
{
}

void ModeratorSequence::Update(const float& dt)
{
}

void ModeratorSequence::Draw()
{
}

void ModeratorSequence::Release()
{

}
