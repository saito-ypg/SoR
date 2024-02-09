#include<cmath>
#include "GameActor.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"HPBar.h"
#include"Engine/Image.h"
#include"Engine/Debug.h"

GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
	isInvincible_ = false;
	isDead_ = false;
	hCircle_ = -1;
	hQuad_ = -1;
	hSector_ = -1;
	hCircle_ = Model::Load("Assets\\Area\\CircleArea.fbx");
	hQuad_ = Model::Load("Assets\\Area\\QuadArea.fbx");
	hSector_ = Model::Load("Assets\\Area\\SectorArea.fbx");
	assert(hCircle_ >= 0);
	assert(hQuad_ >= 0);
	assert(hSector_ >= 0);

	knockBack = { 0,0,XMVectorZero() };

}

GameActor::~GameActor()
{

}

void GameActor::Update()
{
	//���낢��X�V�����
	
	ActorUpdate();
	if (knockBack.Time > 0)
	{
		float quart = (1 - std::pow(1 - (defTime - knockBack.Time) / defTime, 4))-(1 - std::pow(1 - (defTime - knockBack.Time-1) / defTime, 4));
		XMVECTOR force = knockBack.Velocity * quart * knockBack.Dir;
		ForceMove(knockBack.Velocity * quart * knockBack.Dir);
		knockBack.Time--;
		if (knockBack.Time <= 0)
			knockBack.Dir = XMVectorZero();
	}

	if (status_.hp_ <= 0)
		KillMe();
}

void GameActor::ActorUpdate()
{
}

void GameActor::Draw()
{
	//�Ȃ񂩂��

	ActorDraw();
	DrawHP();

}
void GameActor::ActorDraw()
{
}
void GameActor::DrawHP()
{
	Transform DrawT;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMStoreFloat3(&DrawT.position_,XMVector3TransformCoord(vPos, Camera::GetViewMatrix() * Camera::GetProjectionMatrix()*Camera::GetVPMatrix()));
	DrawT.position_.z = 0;
	DrawT.position_.x = DrawT.position_.x / Direct3D::scrWidth_* 2.0f - 1;
	DrawT.position_.y = DrawT.position_.y / -Direct3D::scrHeight_ * 2.0f + 1;
	//HPBar::Draw(HPBar::BAR, DrawT);
	/*for (int i = 0; i < HPBar::NUM; i++)
	{
		HPBar::Draw((HPBar::HANDLE)i, DrawT);
	}*/
}


void GameActor::TakeAttacked(DamageData& dmg,XMVECTOR& dir)
{
	status_.hp_ -= dmg.damage_;
	{//�m�N�o����
		knockBack.Velocity = dmg.knockback_;
		knockBack.Time = defTime;
		knockBack.Dir = dir;

	}
	if (dmg.pEffect_) {
		dmg.pEffect_;//�]�T���������������
	}
	Debug::Log("Remain:" + std::to_string(status_.hp_), true);

}
void GameActor::AddColliderCamp(GameActor* act, CAMPS camp)
{    
	CollisionManager::AddCamp(act, camp);
}
void GameActor::RemoveColliderCamp(GameActor* act, CAMPS camp)
{
	CollisionManager::RemoveCamp(act, camp);
}

bool GameActor::CanMove()
{
	return false;
}

void GameActor::SimpleDraw()
{
	if (hModels_.empty())
		return;
	int front = hModels_.front();
	Model::SetTransform(front, transform_);
	Model::Draw(front);
}
void GameActor::DrawCollision()
{
	Transform circle;
	circle.position_ = transform_.position_;
	circle.scale_.x = status_.hitCircleRange_;
	circle.scale_.z = status_.hitCircleRange_;
	Model::SetTransform(hCircle_, circle);
	Model::Draw(hCircle_);

}
Transform* GameActor::GetTransformRef()
{
	return &transform_;
}

void GameActor::ForceMove(XMVECTOR move)
{
	XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
	vpos += move;
	XMStoreFloat3(&transform_.position_, vpos);

}
