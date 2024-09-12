#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"CollisionManager.h"
#include"EnemyManager.h"
#include"ModeratorSequence.h"
#include"Decoy.h"
#include"HPBar.h"
#include"areamodels.h"
#include"PlayerInterface.h"
//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	mod = nullptr;
}

PlayScene::~PlayScene()
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Ground>(this);
	AreaModels::Initialize();
	/*auto p=*/Instantiate<Player>(this);

	mod = Instantiate<ModeratorSequence>(this);
	Camera::SetTarget(XMFLOAT3{ 0,0,-3 });
	Camera::SetPosition(XMFLOAT3{ 0, 23.0f, -20.0f });
	HPBar::Initialize();
	Instantiate<PlayerInterface>(this);


}

//更新
void PlayScene::Update(const float& dt)
{
	CollisionManager::Update(dt);
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
	CollisionManager::Release();
}