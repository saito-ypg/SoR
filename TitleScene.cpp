#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"TitleScene.h"
//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
}

//更新
void TitleScene::Update()
{

}

//描画
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
	CollisionManager::Release();
}