#pragma once
#include"Engine/Transform.h"

class HPBar
{
private:
	XMFLOAT3 position;//hpバーを表示する位置
	float curGauge;//線形補完
	float redGauge;//赤ゲージ。一定時間後減らす?


public:
	void Initialize();
	void Update(float hpRatio);//hp割合入れて表示のための計算
	void Draw();//座標入れて描画。
};

