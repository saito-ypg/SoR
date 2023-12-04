#pragma once
//攻撃範囲の構造体を記述
#include<DirectXMath.h>

using namespace DirectX;
struct AttackRangeBase
{
	
	//中心位置。扇の場合は中心角の位置
	XMFLOAT3 position_;//中心座標
	AttackRangeBase(XMFLOAT3 pos);
};
struct AttackRangeCircle		:public AttackRangeBase//円形の攻撃範囲データ
{
	float radius_;//半径
	AttackRangeCircle(XMFLOAT3 pos);
};
struct AttackRangeQuad			:public AttackRangeBase//矩形の攻撃範囲データ
{
	float width_;//幅
	float length_;//奥行き
	float rotate_;//y軸回転
	AttackRangeQuad(XMFLOAT3 pos);
};
struct AttackRangeCirculerSector :public AttackRangeBase//扇型攻撃範囲データ
{
	float radius_;//半径
	float centerAngle_;//中心角,degree or radianどっち？今のところdeg
	float rotate_;//中心角の二等分線の回転,y軸
	AttackRangeCirculerSector(XMFLOAT3 pos);
};

