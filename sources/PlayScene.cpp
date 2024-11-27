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
	Instantiate<Ground>(this);
	AreaModels::Initialize();
	/*auto p=*/Instantiate<Player>(this);

	mod = Instantiate<ModeratorSequence>(this);
	Camera::SetTarget(XMFLOAT3{ 0,0,-3 });
	Camera::SetPosition(XMFLOAT3{ 0, 23.0f, -20.0f });
	HPBar::Initialize();
	Instantiate<PlayerInterface>(this);


}

//�X�V
void PlayScene::Update(const float& dt)
{
	CollisionManager::Update(dt);
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