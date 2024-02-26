#include "ModeratorSequence.h"
#include"EnemyManager.h"
#include"EnemySpawner.h"
#include<fstream>
#include<algorithm>
#include"libraries/json.hpp"
string DATA_PATH="Assets/data/";
using std::vector;
using namespace std::chrono;


void ModeratorSequence::LoadData()
{
	using namespace std;
	//https://jsoneditoronline.org/#left=local.desuze&right=local.judamu json�G�f�B�^
	string filename = DATA_PATH+"game_stage.json";
	ifstream ifs(filename.c_str());
	if (ifs.good())
	{
		using json = nlohmann::json;
		json stageData;
		ifs >> stageData;
		auto size = stageData.size();
		spawnDataList.resize(size);
		for(auto i=0;i<size;i++)
		{
			auto& game = stageData["Games"].at(i);
			for (auto& stage : game["stage"]) {
				EnemySpawning temp{ 0,EnemyType::MAX,false };
				if (stage.empty())	assert(false);//stage����̏ꍇ

				temp.spawntime= stage["spawn_time"];
				temp.type = TypeMap.at(stage["enemy_type"]);
				temp.is_boss = stage["is_boss"];
				spawnDataList.at(i).emplace_back(temp);
				
			}
			std::sort(spawnDataList.at(i).begin(), spawnDataList.at(i).end());
		}
	}

}
ModeratorSequence::ModeratorSequence(GameObject* parent):GameObject(parent,"ModeratorSequence")
{
	//https://chat.openai.com/share/4c4ae57d-f51a-4ef8-895a-9d1c7068977d
	curTime = milliseconds(0);
	ttlTime = milliseconds(0);
	waves = 0;
	spawnindex = 0;
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
	case CHANGED:
		state = BEGIN;


		break;
	case PREP:

		break;
	case BEGIN:
		if (true) {//���ԏ���
			if (spawnindex < spawnDataList.at(waves).size()) {
				auto& waiting = spawnDataList.at(waves).at(spawnindex);
				if (waiting.spawntime <=static_cast<float>(duration_cast<seconds>(curTime).count()))
				{
					while (spawnindex < spawnDataList.at(waves).size()) {
						manager->add(EnemySpawner::spawnEnemy(this, spawnDataList.at(waves).at(spawnindex).type));
						spawnindex++;
					}
				}
				
			}
				else if (manager->Eliminated())
					state = END;
			curTime += milliseconds(static_cast<long long>(dt));
			ttlTime += milliseconds(static_cast<long long>(dt));
			
		}
	
		break;
	case ModeratorSequence::END:
		spawnindex = 0;
		waves++;
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

