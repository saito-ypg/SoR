#include"../Engine/Camera.h"
#include"../Engine/Input.h"
#include"../Engine/SceneManager.h"
#include"../Engine/Image.h"
#include"ClearScene.h"
//�R���X�g���N�^
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
	hImage = -1;
}

ClearScene::~ClearScene()
{
}

//������
void ClearScene::Initialize()
{
	hImage = Image::Load("Images/Clear.png");
	assert(hImage >= 0);
}

//�X�V
void ClearScene::Update(const float& dt)
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//�`��
void ClearScene::Draw()
{
	Image::SetTransform(hImage, transform_);
	Image::Draw(hImage);
}

//�J��
void ClearScene::Release()
{

}