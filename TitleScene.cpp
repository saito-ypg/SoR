#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"TitleScene.h"
//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
}

//�X�V
void TitleScene::Update()
{

}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
	CollisionManager::Release();
}