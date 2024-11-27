#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"Engine/Image.h"
#include"GameOverScene.h"
//�R���X�g���N�^
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene")
{
	hImage = -1;
}

GameOverScene::~GameOverScene()
{
}

//������
void GameOverScene::Initialize()
{
	hImage = Image::Load("Images/GameOver.png");
	assert(hImage >= 0);
}

//�X�V
void GameOverScene::Update(const float& dt)
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//�`��
void GameOverScene::Draw()
{
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//�J��
void GameOverScene::Release()
{

}