#pragma once
#include "../Engine/GameObject.h"

class Text;
class TitleScene : public GameObject
{
	int hImage;
	Text* pText;
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