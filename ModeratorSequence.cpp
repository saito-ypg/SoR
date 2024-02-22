#include "ModeratorSequence.h"
#include"EnemyManager.h"
ModeratorSequence::ModeratorSequence(GameObject* parent):GameObject(parent,"ModeratorSequence")
{
	//https://chat.openai.com/share/4c4ae57d-f51a-4ef8-895a-9d1c7068977d
	curTime = milliseconds(0);
	ttlTime = milliseconds(0);
	waves = 0;
	state = BEGIN;
	manager = nullptr;
}

ModeratorSequence::~ModeratorSequence()
{
	
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
			curTime +=milliseconds(static_cast<long long>(dt));
			ttlTime += milliseconds(static_cast<long long>(dt));
			
		}
		if (manager->Eliminated())
			state = END;
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
