#pragma once
#include"Engine/Transform.h"

class HPBar
{
private:
	XMFLOAT3 position;//hp�o�[��\������ʒu
	float curGauge;//���`�⊮
	float redGauge;//�ԃQ�[�W�B��莞�Ԍ㌸�炷?


public:
	void Initialize();
	void Update(float hpRatio);//hp��������ĕ\���̂��߂̌v�Z
	void Draw();//���W����ĕ`��B
};

