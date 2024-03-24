#pragma once
#include "../Engine/GameObject.h"


class GameOverScene : public GameObject
{
	int hImage;
public:

	GameOverScene(GameObject* parent);

	virtual ~GameOverScene();
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update(const float& dt) override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};