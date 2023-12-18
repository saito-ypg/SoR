#pragma once
//ダメージを受ける際に必要な情報を格納
struct DamageData
{
	float damage_;//ダメージ量
	float direction_;//攻撃の方向、ノックバックする向き(y軸回転、deg)
	float knockback_;//ノックバック強さ
	DamageData() :damage_(0), direction_(0), knockback_(0) {}
};

