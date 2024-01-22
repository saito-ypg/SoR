#pragma once
#include"Engine/Transform.h"

namespace HPBar
{
	enum HANDLE {
		BASE = 0,
		DMG,
		BAR,
		FRAME,
		NUM
	};
	void Initialize();
	void Update(float hpRatio);//hp割合入れて表示のための計算
	void Draw();//座標入れて描画。
};

