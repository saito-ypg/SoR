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
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update(const float& dt) override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};