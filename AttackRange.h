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
	AREATYPE areatype_;//�U���G���A�B�v������
	float a_;
	float b_;
	float c_;
	AttackRangeBase(XMFLOAT3 pos);
};
struct AttackRangeCircle		:public AttackRangeBase//�~�`�̍U���͈̓f�[�^
{
	float &radius_=a_;//���a
	AttackRangeCircle(XMFLOAT3 pos);
};
struct AttackRangeQuad			:public AttackRangeBase//��`�̍U���͈̓f�[�^
{
	float &width_=a_;//��������̕��A���ۂ͔{�B��(Z+����)�����ʂƂ�������X��������width,
	float &length_ = b_;//��������̉��s���A���ۂ͔{�B��(Z+����)�����ʂƂ�������Z��������width,
	float &rotate_=c_;//y����]
	AttackRangeQuad(XMFLOAT3 pos);
};
struct AttackRangeCirculerSector :public AttackRangeBase//��^�U���͈̓f�[�^
{
	float &radius_=a_;//���a
	float &centerAngle_=b_;//�Б��̊J����Adeg�œ���
	float &rotate_=c_;//���S�p�̓񓙕����̉�],y��
	AttackRangeCirculerSector(XMFLOAT3 pos);
};

