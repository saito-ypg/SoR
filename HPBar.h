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
	void Update(float hpRatio);//hp��������ĕ\���̂��߂̌v�Z
	void Draw();//���W����ĕ`��B
};

