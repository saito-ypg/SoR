#include "ModeratorSequence.h"
#include"EnemyManager.h"
#include<fstream>
#include"libraries/json.hpp"
string DATA_PATH="Assets/data/";
void ModeratorSequence::LoadData()
{
	using namespace std;
	//https://jsoneditoronline.org/#left=local.desuze&right=local.judamu jsonエディタ
	string filename = DATA_PATH+"game_stage.json";
	ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		using json = nlohmann::json;
		json stageData;
		ifs >> stageData;
		for(auto& game:stageData["Games"])
		{
			spawnDataList.push_back();
			for (auto& stage : game["stage"]) {
				EnemySpawning temp;
				temp;
				if (stage.empty())	assert(false);//stageが空の場合

				temp.spawntime= stage["spawn_time"];
				temp.type = TypeMap.at(stage["eneym_type"]);
				temp.is_boss = stage["is_boss"];

			}

		}
	
	}

}
ModeratorSequence::ModeratorSequence(GameObject* parent):GameObject(parent,"ModeratorSequence")
{
	//https://chat.openai.com/share/4c4ae57d-f51a-4ef8-895a-9d1c7068977d
	curTime = milliseconds(0);
	ttlTime = milliseconds(0);
	waves = 0;
	state = CHANGED;
	manager = nullptr;
}

ModeratorSequence::~ModeratorSequence()
{
	
}

void ModeratorSequence::Initialize()
{
	manager = new EnemyManager(this);
	LoadData();

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
