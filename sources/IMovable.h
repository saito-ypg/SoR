#pragma once
#include<DirectXMath.h>
using namespace DirectX;

//�ړ�����N���X���O���Ɉړ��x�N�g�������J���邽�߂̃C���^�[�t�F�[�X
class IMovable
{	
public:
	virtual XMVECTOR GetVelocity()const=0;
	virtual ~IMovable()=default;
};

