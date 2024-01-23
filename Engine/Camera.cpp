#include "Camera.h"

namespace Camera{	
	XMVECTOR position_;	//カメラの位置（視点）
	XMVECTOR target_;	//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列
}

//初期化
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);
	target_ = XMVectorSet(0, 0, 0, 0);

	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//更新
void Camera::Update()
{
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//位置を設定
void Camera::SetPosition(XMVECTOR position)
{
	Camera::position_ = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	SetPosition(XMLoadFloat3(&position));
}

//焦点を設定
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

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

//プロジェクション行列を取得
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
