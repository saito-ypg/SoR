#include "ModeratorSequence.h"
#include"EnemyManager.h"
ModeratorSequence::ModeratorSequence(GameObject* parent):GameObject(parent,"ModeratorSequence")
{
	curTime = 0;
	ttlTime = 0;
	waves = 0;
	state = BEGIN;
	manager = nullptr;
}

ModeratorSequence::~ModeratorSequence()
{
	Release();
}

void ModeratorSequence::Initialize()
{
	manager = new EnemyManager(this);
}

void ModeratorSequence::Update(const float& dt)
{
	switch (state)
	{
	case ModeratorSequence::PREP:

		break;
	case ModeratorSequence::BEGIN:
		if (true) {
			curTime += dt;
			ttlTime += dt;
			
		}
		break;
	case ModeratorSequence::END:
		break;

	}
}

void ModeratorSequence::Draw()
{
}

void ModeratorSequence::Release()
{
	manager->Release();
	delete manager;
}
