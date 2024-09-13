#pragma once
//ダメージを受ける際に必要な情報を格納
struct EffectData {


};
struct DamageData
{
	float damage_;//ダメージ量
	float knockback_;//ノックバック強さ
	float duration_;//攻撃持続ミリ秒
	float maxDuration;
	EffectData* pEffect_;
	DamageData() :damage_(0), knockback_(0),duration_(0),maxDuration(0),pEffect_(nullptr) {}
};
