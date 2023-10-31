#include "PlayScene.h"
#include"Player.h"
#include"Ground.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{

	Instantiate<Player>(this);
	Instantiate<Ground>(this);
	Camera::SetTarget(XMFLOAT3{ 0,0,0 });
	Camera::SetPosition(XMFLOAT3{ 0, 30, -20 });
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}