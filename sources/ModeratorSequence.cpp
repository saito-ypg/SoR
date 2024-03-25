#include<fstream>
#include<algorithm>
#include<string>
#include<sstream>
#include<iomanip>	
#include "ModeratorSequence.h"
#include"EnemyManager.h"
#include"EnemySpawner.h"
#include"../Engine/SceneManager.h"
#include"../Engine/Image.h"	
#include"../libraries/json.hpp"

using std::string;
const string DATA_PATH="data/";
using std::vector;
using namespace std::chrono;
constexpr float TRANSITION_MS = 3000;
constexpr int MAX_WAVE = 2;
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
	hImage[0] = -1;
	hImage[1] = -1;
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
	pText = new Text();
	pText->Initialize();
	hImage[0] = Image::Load("Images/inc.png");
	hImage[1] = Image::Load("Images/waveclear.png");
	assert(hImage[0] >= 0);
	assert(hImage[1] >= 0);
}

void ModeratorSequence::Update(const float& dt)
{
	auto Transition = [&](ModeratorSequence::s nextState) {
		transitionTime -= dt; 
		if (transitionTime < 0)
			state = nextState;
		return (transitionTime < 0);
	};
	switch (state)
	{
	case CHANGED:
	
		if (Transition(PREP)) {
			transitionTime = TRANSITION_MS;
			
		}break;
	case PREP:
		Transition(BEGIN);
		
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
		manager->clearEnemy();
		if (waves >= MAX_WAVE)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_CLEAR);
		}
		state = PREP;
		transitionTime = TRANSITION_MS;
		break;
	case GAMEOVER:
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		break;
	}
	manager->Update(dt);
}

void ModeratorSequence::Draw()
{
	Transform pictT;
	pictT.position_ = XMFLOAT3(0, 0, 0);
	switch (state)
	{

	case ModeratorSequence::PREP:
		
		Image::SetTransform(hImage[0], pictT);
		Image::Draw(hImage[0]);
		break;
	case ModeratorSequence::END	:
		Image::SetTransform(hImage[1], pictT);
		Image::Draw(hImage[1]);
		break;
	}
	auto ms = ttlTime;
	auto secs = std::chrono::duration_cast<std::chrono::seconds>(ms);
	ms -= std::chrono::duration_cast<std::chrono::milliseconds>(secs);
	auto mins = std::chrono::duration_cast<std::chrono::minutes>(secs);
	secs -= std::chrono::duration_cast<std::chrono::seconds>(mins);
	std::stringstream timestr;
	timestr <<"TIME:" << std::setw(2) << std::setfill('0') << mins.count() << ":"
		<< std::setw(2) << std::setfill('0') << secs.count() << ":"
		<< std::setw(3) << std::setfill('0') << ms.count();
	pText->Draw(10, 32, timestr.str().c_str());
	std::stringstream wavestr;
	wavestr << "WAVES:" << waves+1;
	pText->Draw(10, 64,wavestr.str().c_str());
}

void ModeratorSequence::Release()
{
	manager->Release();
	delete manager;
}

