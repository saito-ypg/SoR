#include"../Engine/Camera.h"
#include"../Engine/Input.h"
#include"../Engine/SceneManager.h"
#include"../Engine/Image.h"
#include"ClearScene.h"
//コンストラクタ
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
	hImage = -1;
}

ClearScene::~ClearScene()
{
}

//初期化
void ClearScene::Initialize()
{
	hImage = Image::Load("Images/Clear.png");
	assert(hImage >= 0);
}

//更新
void ClearScene::Update(const float& dt)
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//描画
void ClearScene::Draw()
{
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//開放
void ClearScene::Release()
{

}