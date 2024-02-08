#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"TitleScene.h"
#include"Engine/Image.h"
//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
	hImage = -1;
}

TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	hImage = Image::Load("Assets/title.png");
	assert(hImage >= 0);
}

//�X�V
void TitleScene::Update()
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
}

//�J��
void TitleScene::Release()
{
	Image::Release(hImage);
}