#pragma once
#include "Engine/GameObject.h"


class ClearScene : public GameObject
{
	int hImage;
public:

	ClearScene(GameObject* parent);

	virtual ~ClearScene();
	//初期化
	void Initialize() override;

	//更新
	void Update(const float& dt) override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};