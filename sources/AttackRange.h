#pragma once
//攻撃範囲の構造体を記述
#include<DirectXMath.h>
#include<functional>
#include "areamodels.h"
using namespace DirectX;
struct actorAddr;
struct AttackRangeBase
{
	//中心位置。扇の場合は中心角の位置
	XMFLOAT3 position_;//中心座標
	AttackRangeBase();
	AttackRangeBase(XMFLOAT3 pos);
	AreaModels::AREATYPE getType() const { return areatype_; }
	virtual bool IsHit(struct actorAddr& data)=0;
	virtual XMVECTOR getDir(XMFLOAT3 pos)const = 0;//当たり判定の中心と対象との距離をとる
protected:
	AreaModels::AREATYPE areatype_;//攻撃エリア。要初期化


};
struct AttackRangeCircle		:public AttackRangeBase//円形の攻撃範囲データ
{
	
	float radius_;//半径
	AttackRangeCircle();
	AttackRangeCircle(XMFLOAT3 pos);
	bool IsHit(struct actorAddr &data)override;
	XMVECTOR getDir(XMFLOAT3 pos)const override;
};
struct AttackRangeQuad			:public AttackRangeBase//矩形の攻撃範囲データ
{
	float width_;//中央からの幅、実際は倍。奥(Z+方向)が正面とした時のX軸成分がwidth,
	float length_;//中央からの奥行き、実際は倍。奥(Z+方向)が正面とした時のZ軸成分がwidth,
	float rotate_;//y軸回転
	AttackRangeQuad();
	AttackRangeQuad(XMFLOAT3 pos);
	bool IsHit(struct actorAddr& data)override;
	XMVECTOR getDir(XMFLOAT3 pos)const override;
};
struct AttackRangeCirculerSector :public AttackRangeBase//扇型攻撃範囲データ
{
	float radius_;//半径
	float centerAngle_;//片側の開き具合、degで入力
	float rotate_;//中心角の二等分線の回転,y軸
	AttackRangeCirculerSector();
	AttackRangeCirculerSector(XMFLOAT3 pos);
	bool IsHit(struct actorAddr& data)override;
	XMVECTOR getDir(XMFLOAT3 pos)const override;
};

