#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"Engine/Image.h"
#include"GameOverScene.h"
//コンストラクタ
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene")
{
	hImage = -1;
}

GameOverScene::~GameOverScene()
{
}

//初期化
void GameOverScene::Initialize()
{
	hImage = Image::Load("Images/GameOver.png");
	assert(hImage >= 0);
}

//更新
void GameOverScene::Update(const float& dt)
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//描画
void GameOverScene::Draw()
{
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//開放
void GameOverScene::Release()
{

}