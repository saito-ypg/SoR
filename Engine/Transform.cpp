#include "Transform.h"



Transform::Transform(): pParent_(nullptr)
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
}


Transform::~Transform()
{
}

void Transform::Calclation()
{
	//�ړ��s��
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//��]�s��
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//�g��k��
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix() 
{
	Calclation();
	if (pParent_)
	{
		return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	return  matScale_ * matRotate_ * matTranslate_;
}

XMFLOAT3 operator+(const XMFLOAT3& left, const XMFLOAT3& right)
{
	return XMFLOAT3(left.x + right.x, left.y + right.y, left.z + right.z);
}

XMFLOAT3 operator-(const XMFLOAT3& left, const XMFLOAT3& right)
{
	return XMFLOAT3(left.x - right.x, left.y - right.y, left.z - right.z);
}
