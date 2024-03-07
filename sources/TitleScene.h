#pragma once
#include "../Engine/GameObject.h"


class TitleScene : public GameObject
{
	int hImage;
public:

	TitleScene(GameObject* parent);

	virtual ~TitleScene();
	//������
	void Initialize() override;

	//�X�V
	void Update(const float& dt) override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};