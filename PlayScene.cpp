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
	
	Instantiate<Player>(this);
	Instantiate<Ground>(this);
	mod = Instantiate<ModeratorSequence>(this);
	//Instantiate<Decoy>(this);
	auto* d = Instantiate<Decoy>(this);
	d->SetPosition(XMFLOAT3(1, 0, 10));
	d->SetRotateY(45);
	Camera::SetTarget(XMFLOAT3{ 0,0,0 });
	Camera::SetPosition(XMFLOAT3{ 0, 30, -20.0f });
	HPBar::Initialize();

}

//更新
void PlayScene::Update(const float& dt)
{
	CollisionManager::Update();
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