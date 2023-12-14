#pragma once
#include<DirectXMath.h>
//ダメージを受ける際に必要な情報を格納
struct DamageData
{
	float damage_;//ダメージ量
	float direction_;//攻撃の方向、ノックバックする向き(y軸回転、deg)
	float knockback_;//ノックバック強さ
};

