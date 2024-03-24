#pragma once
#include "../Engine/GameObject.h"


class ClearScene : public GameObject
{
	int hImage;
public:

	ClearScene(GameObject* parent);

	virtual ~ClearScene();
	//������
	void Initialize() override;

	//�X�V
	void Update(const float& dt) override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};