#pragma once
class ActorInfo
{
public:
	float hp_;
	float maxHp_;
	float hitCircleRange_;//���a
	ActorInfo() :hp_(0), maxHp_(0), hitCircleRange_(0) {};
	/// <summary>
	/// �A�N�^�[�̊�b���
	/// </summary>
	/// <param name="maxHp">�ő�HP</param>
	/// <param name="range">�����蔻��̉~�̔��a</param>
	ActorInfo(float maxHp, float range):hp_(maxHp),maxHp_(maxHp),hitCircleRange_(range){}
};

