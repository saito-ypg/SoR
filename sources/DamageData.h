#pragma once
//�_���[�W���󂯂�ۂɕK�v�ȏ����i�[
struct EffectData {


};
struct DamageData
{
	float damage_;//�_���[�W��
	float knockback_;//�m�b�N�o�b�N����
	float duration_;//�U�������~���b
	float maxDuration_;
	EffectData* pEffect_;
	DamageData() :damage_(0), knockback_(0),duration_(0), maxDuration_(0),pEffect_(nullptr) {}
	DamageData(float dmg, float kb, float dur) :damage_(dmg), knockback_(kb), duration_(dur), maxDuration_(dur), pEffect_(nullptr) {}
	
};
