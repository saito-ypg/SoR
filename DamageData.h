#pragma once
//�_���[�W���󂯂�ۂɕK�v�ȏ����i�[
struct DamageData
{
	float damage_;//�_���[�W��
	float direction_;//�U���̕����A�m�b�N�o�b�N�������(y����]�Adeg)
	float knockback_;//�m�b�N�o�b�N����
	DamageData() :damage_(0), direction_(0), knockback_(0) {}
};

