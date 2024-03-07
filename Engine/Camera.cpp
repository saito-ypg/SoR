#include "camera.h"
#include "Direct3D.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _billBoard;

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//カメラの位置
	_target = XMFLOAT3( 0, 0, 0);	//カメラの焦点

	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::scrWidth / (FLOAT)Direct3D::scrHeight, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));


	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target)- XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//焦点を設定
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//位置を設定
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//焦点を取得
XMFLOAT3 Camera::GetTarget() { return _target; }

XMVECTOR Camera::GetTargetV()
{
	return XMLoadFloat3(&_target);
}

//位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

XMVECTOR Camera::GetPositionV()
{
	return XMLoadFloat3(&_position);
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

XMMATRIX Camera::GetVPMatrix()
{
	float w = (float)(Direct3D::scrWidth/ 2.0f);
	float h = (float)(Direct3D::scrHeight / 2.0f);
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
	return XMMatrixInverse(nullptr, GetVPMatrix()) * XMMatrixInverse(nullptr, _proj) * XMMatrixInverse(nullptr, _view);
}

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix(){	return _billBoard; }
