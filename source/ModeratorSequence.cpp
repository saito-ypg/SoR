#include "ModeratorSequence.h"
#include"EnemyManager.h"
#include"EnemySpawner.h"
#include<fstream>
#include<algorithm>
#include"../libraries/json.hpp"
const string DATA_PATH="Assets/data/";
using std::vector;
using namespace std::chrono;
constexpr float TRANSITION_MS = 3000;

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
		auto size = stageData["Waves"].size();
		spawnDataList.resize(size);
		for(auto i=0;i<size;i++)
		{
			auto& game = stageData["Waves"].at(i);
			for (auto& stage : game["enemy"]) {
				EnemySpawning temp;
				if (stage.empty())	assert(false);//stageが空の場合

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
	transitionTime = TRANSITION_MS;

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
	auto Transition = [&](ModeratorSequence::s nextState) {transitionTime -= dt; if (transitionTime < 0)state = nextState; };
	switch (state)
	{
	case CHANGED:
	
		Transition(BEGIN);
	
		break;
	case PREP:

		Transition(BEGIN);
		transitionTime = TRANSITION_MS;
		break;
	case BEGIN:
		if (true) {//時間条件
			auto size = spawnDataList.at(waves).size();
			if (spawnindex <size ) {
				auto& waiting = spawnDataList.at(waves).at(spawnindex);
				float time = static_cast<float>(duration_cast<seconds>(curTime).count());
				if (waiting.spawntime <=time)
				{
						manager->add(EnemySpawner::spawnEnemy(this, spawnDataList.at(waves).at(spawnindex).type));	
						spawnindex++;
				}
				
			}
			else if (manager->Eliminated())
			{
				state = END;
				transitionTime = TRANSITION_MS;
			}
			curTime += milliseconds(static_cast<long long>(dt));
			ttlTime += milliseconds(static_cast<long long>(dt));
			
		}
	
		break;
	case END:

		Transition(NEXT);

		break;
	case NEXT:
		spawnindex = 0;
		waves++;
		state = PREP;
		transitionTime = TRANSITION_MS;
	}
	manager->Update(dt);
}

void ModeratorSequence::Draw()
{
}

void ModeratorSequence::Release()
{
	manager->Release();
	delete manager;
}

