#pragma once
#include "Engine/GameObject.h"
#include<memory>
class ModeratorSequence;

//�����V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
private:
	ModeratorSequence* mod;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	virtual ~PlayScene();
	//������
	void Initialize() override;

	//�X�V
	void Update(const float& dt) override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};