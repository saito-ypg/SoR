#pragma once
#include<DirectXMath.h>
using namespace DirectX;

//移動するクラスが外部に移動ベクトルを公開するためのインターフェース
class IMovable
{	
public:
	virtual XMVECTOR GetVelocity()const=0;
	virtual ~IMovable()=default;
};

