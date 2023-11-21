#pragma once
#include"Engine/Transform.h"


class ActorCollider //キャラ毎の当たり判定の大きさ
{	
private:
	
protected:
	Transform transform_;//所属オブジェクトの値をそのまま持っとく。更新は…どうしよう
public:
	Transform offset_;//所属オブジェクトからのオフセット、なければALL0
	ActorCollider();
	~ActorCollider();

};

