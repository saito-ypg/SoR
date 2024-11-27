#pragma once
//�U���͈͂̍\���̂��L�q
#include<DirectXMath.h>
#include<functional>
#include "areamodels.h"
using namespace DirectX;
struct actorAddr;
struct AttackRangeBase
{
	//���S�ʒu�B��̏ꍇ�͒��S�p�̈ʒu
	XMFLOAT3 position_;//���S���W
	AttackRangeBase();
	AttackRangeBase(XMFLOAT3 pos);
	AreaModels::AREATYPE getType() const { return areatype_; }
	virtual bool IsHit(struct actorAddr& data)=0;
	virtual XMVECTOR getDir(XMFLOAT3 pos)const = 0;//�����蔻��̒��S�ƑΏۂƂ̋������Ƃ�
protected:
	AreaModels::AREATYPE areatype_;//�U���G���A�B�v������


};
struct AttackRangeCircle		:public AttackRangeBase//�~�`�̍U���͈̓f�[�^
{
	
	float radius_;//���a
	AttackRangeCircle();
	AttackRangeCircle(XMFLOAT3 pos);
	bool IsHit(struct actorAddr &data)override;
	XMVECTOR getDir(XMFLOAT3 pos)const override;
};
struct AttackRangeQuad			:public AttackRangeBase//��`�̍U���͈̓f�[�^
{
	float width_;//��������̕��A���ۂ͔{�B��(Z+����)�����ʂƂ�������X��������width,
	float length_;//��������̉��s���A���ۂ͔{�B��(Z+����)�����ʂƂ�������Z��������width,
	float rotate_;//y����]
	AttackRangeQuad();
	AttackRangeQuad(XMFLOAT3 pos);
	bool IsHit(struct actorAddr& data)override;
	XMVECTOR getDir(XMFLOAT3 pos)const override;
};
struct AttackRangeCirculerSector :public AttackRangeBase//��^�U���͈̓f�[�^
{
	float radius_;//���a
	float centerAngle_;//�Б��̊J����Adeg�œ���
	float rotate_;//���S�p�̓񓙕����̉�],y��
	AttackRangeCirculerSector();
	AttackRangeCirculerSector(XMFLOAT3 pos);
	bool IsHit(struct actorAddr& data)override;
	XMVECTOR getDir(XMFLOAT3 pos)const override;
};

