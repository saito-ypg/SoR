#pragma once
//�U���͈͂̍\���̂��L�q
#include<DirectXMath.h>
enum AREATYPE {
	CIRCLE, QUAD, SECTOR, NONE
};
using namespace DirectX;
struct AttackRangeBase
{

	//���S�ʒu�B��̏ꍇ�͒��S�p�̈ʒu
	XMFLOAT3 position_;//���S���W
	float Duration;//���莝���t���[��
	AttackRangeBase();
	AttackRangeBase(XMFLOAT3 pos);
	AREATYPE getType() { return areatype_; }
	virtual bool IsHit(struct actorAddr& data)=0;
protected:
	AREATYPE areatype_;//�U���G���A�B�v������
	//float a_;
	//float b_;
	//float c_;

};
struct AttackRangeCircle		:public AttackRangeBase//�~�`�̍U���͈̓f�[�^
{
	
	float radius_;//���a
	AttackRangeCircle();
	AttackRangeCircle(XMFLOAT3 pos);
	bool IsHit(struct actorAddr &data)override;
};
struct AttackRangeQuad			:public AttackRangeBase//��`�̍U���͈̓f�[�^
{
	float width_;//��������̕��A���ۂ͔{�B��(Z+����)�����ʂƂ�������X��������width,
	float length_;//��������̉��s���A���ۂ͔{�B��(Z+����)�����ʂƂ�������Z��������width,
	float rotate_;//y����]
	AttackRangeQuad();
	AttackRangeQuad(XMFLOAT3 pos);
	bool IsHit(struct actorAddr& data)override;
};
struct AttackRangeCirculerSector :public AttackRangeBase//��^�U���͈̓f�[�^
{
	float radius_;//���a
	float centerAngle_;//�Б��̊J����Adeg�œ���
	float rotate_;//���S�p�̓񓙕����̉�],y��
	AttackRangeCirculerSector();
	AttackRangeCirculerSector(XMFLOAT3 pos);
	bool IsHit(struct actorAddr& data)override;
};

