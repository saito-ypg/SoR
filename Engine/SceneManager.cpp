#include "SceneManager.h"
#include"global.h"
#include"../TestScene.h"
#include"../PlayScene.h"
SceneManager::SceneManager(GameObject* parent) :GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_PLAY;
	nextSceneID_ = SCENE_ID_PLAY;
	Instantiate<PlayScene>(this);
}

void SceneManager::Update()
{
	/*�V�[����؂�ւ�
	���݂Ǝ����ʂ�������؂�ւ�
	���݂̃V�[���̌�Еt��
	�V�����V�[���̏���*/
	if (currentSceneID_ != nextSceneID_)
	{
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();
		
		switch (nextSceneID_) {
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this); break;
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this); break;
		}
		currentSceneID_ = nextSceneID_;

	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
/// <summary>
/// �w�肵���V�[����nextSceneID_�ɐݒ肷��i������Update���Ă΂ꂽ�Ƃ��ɐ؂�ւ��j
/// </summary>
/// <param name="_next"></param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}