#pragma once
//�U���͈͂̍\���̂��L�q
#include<DirectXMath.h>

using namespace DirectX;
struct AttackRangeBase
{
	
	//���S�ʒu�B��̏ꍇ�͒��S�p�̈ʒu
	XMFLOAT3 position_;//���S���W
	AttackRangeBase(XMFLOAT3 pos);
};
struct AttackRangeCircle		:public AttackRangeBase//�~�`�̍U���͈̓f�[�^
{
	float radius_;//���a
	AttackRangeCircle(XMFLOAT3 pos);
};
struct AttackRangeQuad			:public AttackRangeBase//��`�̍U���͈̓f�[�^
{
	float width_;//��������̕��A���ۂ͔{�B��(Z+����)�����ʂƂ�������X��������width,
	float length_;//��������̉��s���A���ۂ͔{�B��(Z+����)�����ʂƂ�������Z��������width,
	float rotate_;//y����]
	AttackRangeQuad(XMFLOAT3 pos);
};
struct AttackRangeCirculerSector :public AttackRangeBase//��^�U���͈̓f�[�^
{
	float radius_;//���a
	float centerAngle_;//�Б��̊J����Adeg�œ���
	float rotate_;//���S�p�̓񓙕����̉�],y��
	AttackRangeCirculerSector(XMFLOAT3 pos);
};

