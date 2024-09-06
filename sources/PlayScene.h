#pragma once
#include "Engine/GameObject.h"
class ModeratorSequence;

class PlayScene : public GameObject
{
private:
	ModeratorSequence* mod;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	virtual ~PlayScene();
	//初期化
	void Initialize() override;

	//更新
	void Update(const float& dt) override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};