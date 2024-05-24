#include"../Engine/Camera.h"
#include"../Engine/Input.h"
#include"../Engine/SceneManager.h"
#include"../Engine/Image.h"
#include"TitleScene.h"
//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
	hImage = -1;
	hTest = -1;
}

TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	hImage = Image::Load("Images/title.png");
	assert(hImage >= 0);

}

//�X�V
void TitleScene::Update(const float& dt)
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//�`��
void TitleScene::Draw()
{
	using namespace Image;
	transform_.scale_ = { 0.6f,0.6f,0.6f };
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//�J��
void TitleScene::Release()
{

}