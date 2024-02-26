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
//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	mod = nullptr;
}

PlayScene::~PlayScene()
{
}

//������
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

//�X�V
void PlayScene::Update(const float& dt)
{
	CollisionManager::Update();
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
	CollisionManager::Release();
}