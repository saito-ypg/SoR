#pragma once
#include "../Engine/GameObject.h"


class GameOverScene : public GameObject
{
	int hImage;
public:

	GameOverScene(GameObject* parent);

	virtual ~GameOverScene();
	//������
	void Initialize() override;

	//�X�V
	void Update(const float& dt) override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};