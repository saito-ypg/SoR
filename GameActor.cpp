#include "GameActor.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"HPBar.h"
#include"Engine/Image.h"
GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
	isInvincible_ = false;
	hCircle_ = -1;
	hQuad_ = -1;
	hSector_ = -1;
	hCircle_ = Model::Load("Assets\\Area\\CircleArea.fbx");
	hQuad_ = Model::Load("Assets\\Area\\QuadArea.fbx");
	hSector_ = Model::Load("Assets\\Area\\SectorArea.fbx");
	assert(hCircle_ >= 0);
}

GameActor::~GameActor()
{

}

void GameActor::Update()
{
	//Ç¢ÇÎÇ¢ÇÎçXêVì¸ÇÍÇÈ
	
	ActorUpdate();

}

void GameActor::Draw()
{
	//Ç»ÇÒÇ©Ç‚ÇÈ

	ActorDraw();
	DrawHP();

}
void GameActor::DrawHP()
{
	int h = Image::Load("Assets/Interface/ball1.png");
	Transform t;
	t.scale_ = XMFLOAT3(0.1, 0.1, 0.1);
	Image::SetTransform(h,t );
	Image::Draw(h);
	//Transform DrawT;
	//XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	//XMStoreFloat3(&DrawT.position_,XMVector3TransformCoord(vPos, Camera::GetViewMatrix() * Camera::GetProjectionMatrix()/**Camera::GetVPMatrix()*/));
	//for (int i = 0; i < HPBar::NUM; i++)
	//{
	//	HPBar::Draw((HPBar::HANDLE)i, DrawT);
	//}
}


void GameActor::TakeAttacked()
{
	KillMe();//ëÃóÕä÷åWÇ≈Ç´ÇÈÇ‹Ç≈ébíË
}
void GameActor::AddColliderCamp(GameActor* act, CAMPS camp)
{    
	CollisionManager::AddCamp(act, camp);
}
void GameActor::RemoveColliderCamp(GameActor* act, CAMPS camp)
{
	CollisionManager::RemoveCamp(act, camp);
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
