#include"../Engine/Camera.h"
#include"../Engine/Input.h"
#include"../Engine/SceneManager.h"
#include"../Engine/Image.h"
#include"TitleScene.h"
//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
	hImage = -1;
}

TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
	hImage = Image::Load("Assets/title.png");
	assert(hImage >= 0);
}

//更新
void TitleScene::Update(const float& dt)
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TitleScene::Draw()
{
	transform_.scale_ = { 0.4f,0.4f,0.4f };
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//開放
void TitleScene::Release()
{

}