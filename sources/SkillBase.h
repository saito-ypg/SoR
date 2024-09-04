#pragma once
#include<vector>
#include<string>
#include"../Engine/Transform.h"
#include"areamodels.h"
#include"AttackRange.h"
#include"DamageData.h"

using namespace AreaModels;
class Player;
///�v���C���[�p�X�L���̊�b�N���X�B�e��p�����[�^�[�͈�U�t���[���P�ʂŎw��B
///�e�h�����action�̒���step���ɏ����ς���(switch-case)�B�K�v�Ȃ��p��enum���B
/// �R���X�g���N�^��CastTime�ECoolDown�̎w��
/// sequence�̃t���[�����w����s������
class SkillBase
{
private:
	/// <summary>
	/// �h���悩��͈����t���̂��̂��ĂԁB����͊�b�I�ȏ������݂̂��s��
	/// </summary>
	SkillBase();
protected:
	Transform beginTransform_;//�X�L���������̃g�����X�t�H�[�����i�[���Ă����B�������ȊO�͊�{������Ȃ��B�v���C���[�̂��̂Ƃ͋�ʂ���
	std::vector<float>sequence{0};//�U���ɂ�����e�X�e�b�v���ԁA�~���b
	float steptime;//�e�X�e�b�v�ł̎c�莞��
	int stepindex;//���݉��X�e�b�v�ڂ��Bsequence
	bool isStepChanged;
	enum base_steps {//��{�I�ȃX�e�b�v
		INVOKED = 0,//��������A�\������Ƃ�
		START_ATTACK,//�U������J�n
		END_ATTACK,//�U������I��
	};
	/// <summary>
	/// UI�N���X�p�A�摜�Ɏg�����O
	/// </summary>
    std::string IconImageName;

	/// <summary>
	/// �X�L���������̓���Ə����̎���
	/// </summary>
	virtual void action() = 0;
	
	/// <summary>
	/// �e�X�e�b�v�̏������Ăѕ�����
	/// </summary>
	void SwitchActionByStep();
	
	/// <summary>
	/// �U���O�X�e�b�v�̎���
	/// </summary>
	virtual void invokedStep()=0;
	
	/// <summary>
	/// �U���J�n�X�e�b�v�̎���
	/// </summary>
	virtual void startStep()=0;
	
	/// <summary>
	/// �U���I����X�e�b�v�̎��� 
	/// </summary>
	virtual void endStep()=0;


	float defaultCastTime_;//�X�L���g�p�㓮���Ȃ�������
	float castTime_;//������悤�ɂȂ�܂ł̎c�莞��
	float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��
	bool isInOperation_;//�X�L���g�p����
	Player* pPlayer_;//�v���C���[�̃X�e�[�^�X�ς����肵�������Ɏg���|�C���^

	void RegisterHitRange(AttackRangeCircle c,DamageData &dmg);
	void RegisterHitRange(AttackRangeQuad q, DamageData &dmg);
	void RegisterHitRange(AttackRangeCirculerSector s, DamageData &dmg);
	Transform GetPlayerTransform();

	/// <summary>
	/// �K�v�Ȃ�p����ł�����I�[�o�[���C�h���A�ŗL�̃����o�Ȃǂ�����������
	/// </summary>
	virtual void ResetInheritedSkillMembers();
public:
	

	/// <summary>
	/// �����̓t���[���P��
	/// </summary>
	/// <param name="CT">�g�p�ɂ����鎞��</param>
	/// <param name="CD">�Ďg�p����</param>
	/// <param name="pPlayer">�v���C���[�̃|�C���^</param>
	SkillBase(const float CT, const float CD, Player *const pPlayer, const std::string iconName);

	virtual ~SkillBase();
	virtual void Update(const float&playerDt);//�X�L�����ԁACD���ԓ��̍X�V�B�v���C���[����X�V�b�����󂯎��i�v���C���[�̎��ԂɑΉ�������)
	void Activate();//�X�L�������i�{�^���������Ƃ��j
	virtual void Draw()=0;//�X�L���G�t�F�N�g�ȂǕ`��
	virtual void DrawRangeDisplay(float deg)=0;//�U���O�ɔ͈͂�\������ ����->�p�x
	virtual void Release() = 0;
	bool CanUse() const{ return coolDown_ <= 0; }
	bool CanMove() const{ return castTime_ <= 0; }
	float getCdPercentage() const;//playerInterface�p�B
	float getCtPercentage() const;//playerInterface�p�B
	bool IsInOperation()const { return isInOperation_; }
	static float ConvFrameToMs(float frames) {return frames*1000 / 60;}//60fps��Ńt���[������~���b�ɕϊ�

	std::string getIconName() const { return IconImageName; };
};

