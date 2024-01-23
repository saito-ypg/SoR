#include "Camera.h"

namespace Camera{	
	XMVECTOR position_;	//�J�����̈ʒu�i���_�j
	XMVECTOR target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
}

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);
	target_ = XMVectorSet(0, 0, 0, 0);

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	Camera::position_ = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	SetPosition(XMLoadFloat3(&position));
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	Camera::target_ = target;
}

void Camera::SetTarget(XMFLOAT3 target)
{
	SetTarget(XMLoadFloat3(&target));
}

XMVECTOR Camera::GetPosition()
{
	return position_;
}

XMVECTOR Camera::GetTarget()
{
	return target_;
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}

XMMATRIX Camera::GetVPMatrix()
{
	float w = (float)(Direct3D::scrWidth_ / 2.0f);
	float h = (float)(Direct3D::scrHeight_ / 2.0f);
	XMMATRIX vp =
	{
	   w,0,0,0,
	   0,-h,0,0,
	   0,0,1,0,
	   w,h,0,1
	};
	return vp;
}

XMMATRIX Camera::GetInverseMatrix()
{
	

	return XMMatrixInverse(nullptr,GetVPMatrix())*XMMatrixInverse(nullptr,projMatrix_)*XMMatrixInverse(nullptr,viewMatrix_);
}
