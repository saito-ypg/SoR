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
	hTest = -1;
}

TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
	hImage = Image::Load("Images/title.png");
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
	using namespace Image;
	transform_.scale_ = { 0.6f,0.6f,0.6f };
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//開放
void TitleScene::Release()
{

}