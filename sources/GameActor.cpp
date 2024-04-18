#include<cmath>
#include "GameActor.h"
#include"../Engine/Model.h"
#include"../Engine/Camera.h"
#include"../Engine/Image.h"
#include"../Engine/Debug.h"
#include"../Engine/Direct3D.h"
#include"HPBar.h"

#include"areamodels.h"

GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
	isInvincible_ = false;
	isdying = false;


	knockBack = { 0,0,XMVectorZero() };

}

GameActor::~GameActor()
{

}

void GameActor::Update(const float& dt)
{
	//Ç¢ÇÎÇ¢ÇÎçXêVì¸ÇÍÇÈ
	
	ActorUpdate(dt);
	if (knockBack.Time > 0)
	{
		float quart =(float)((1 - std::pow(1 - (defTime - knockBack.Time) / defTime, 4))-(1 - std::pow(1 - (defTime - knockBack.Time-1) / defTime, 4)));//outquartÇÃëùï™
		XMVECTOR force = knockBack.Velocity * quart * knockBack.Dir;
		ForceMove(knockBack.Velocity * quart * knockBack.Dir);
		knockBack.Time--;
		if (knockBack.Time <= 0)
			knockBack.Dir = XMVectorZero();
	}

	if (status_.hp_ <= 0)
		isdying = true;
	if (isdying)
	{
		dyingProcess();
	}
}

void GameActor::ActorUpdate(const float& dt)
{
}

void GameActor::Draw()
{
	//Ç»ÇÒÇ©Ç‚ÇÈ

	ActorDraw();

	if (isdying)
		dyingDraw();
	else
	{
		DrawCollision();
		DrawHP();
	}
}
void GameActor::ActorDraw()
{
}
void GameActor::dyingProcess()
{
}
void GameActor::dyingDraw()
{
}
void GameActor::DrawHP()
{
	const float HPBarRatio = 128.0f / Direct3D::screenWidth_;
	
	Transform DrawT;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMStoreFloat3(&DrawT.position_,XMVector3TransformCoord(vPos, Camera::GetViewMatrix() * Camera::GetProjectionMatrix()*Camera::GetVPMatrix()));
	DrawT.position_.z = 0;
	
	DrawT.position_.x = (static_cast<int>((DrawT.position_.x / Direct3D::screenWidth_ - HPBarRatio / 4.0f) * Direct3D::screenWidth_) * 2.0f / Direct3D::screenWidth_) - 1.0f;
	DrawT.position_.y = DrawT.position_.y / -Direct3D::screenHeight_ * 2.0f + 1;
	using namespace HPBar;

	//HPBar::Draw(HPBar::BAR, DrawT);
	for (auto i = 0; i < HPBar::NUM; i++)
	{
		switch (i)
		{
		case DMG:
		case BAR:
			DrawT.scale_.x = status_.hp_ / status_.maxHp_;

			break;
		default:
			DrawT.scale_.x = 1;
		}
		if (DrawT.scale_.x < 0)
			DrawT.scale_.x = 0;
		HPBar::Draw((HPBar::HANDLE)i, DrawT);
	}
}


void GameActor::TakeAttacked(DamageData& dmg,XMVECTOR& dir)
{
	if (isInvincible_)
	{//ñ≥ìGÇÃèàóùÇ†ÇÍÇŒèëÇ≠
		return;
	}
	status_.hp_ -= dmg.damage_;
	{//ÉmÉNÉoèàóù
		knockBack.Velocity = dmg.knockback_/2;
		knockBack.Time = defTime;
		knockBack.Dir = dir;
	}
	if (dmg.pEffect_) {
		//dmg.pEffect_;//ó]óTÇ†Ç¡ÇΩÇÁé¿ëïÇµÇÊ
	}
	XMFLOAT3 fdir;
	XMStoreFloat3(&fdir, -dir);
	transform_.rotate_.y= XMConvertToDegrees((float)atan2(fdir.x, fdir.z));

}
void GameActor::AddColliderCamp(GameActor* act, CAMPS camp)
{    
	CollisionManager::AddCamp(act, camp);
}
void GameActor::RemoveColliderCamp(GameActor* act, CAMPS camp)
{
	CollisionManager::RemoveCamp(act, camp);
}

bool GameActor::CanMoveWithEffects()
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
	Model::SetTransform(area(CIRCLE), circle);
	Model::Draw(area(CIRCLE));

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
