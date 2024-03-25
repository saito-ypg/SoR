#pragma once
#include "../Engine/GameObject.h"


class ClearScene : public GameObject
{
	int hImage;
public:

	ClearScene(GameObject* parent);

	virtual ~ClearScene();
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update(const float& dt) override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};