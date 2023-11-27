#pragma once
#include<DirectXMath.h>
using namespace DirectX;
class ActorCollider //キャラ毎の当たり判定の大きさ
{
private:

protected:

public:
	XMFLOAT3*position_;//所属オブジェクトの値をそのまま持っとく。更新は…どうしよう
	//XMFLOAT3 offset_;//所属オブジェクトからのオフセット、なければALL0
	ActorCollider();
	~ActorCollider();

};

