#include "GameActor.h"
#include"Engine/Model.h"

void GameActor::DrawHP()
{
}

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
	//いろいろ更新入れる
	
	ActorUpdate();

}

void GameActor::Draw()
{
	//なんかやる

	ActorDraw();
}



void GameActor::TakeAttacked()
{
	KillMe();//体力関係できるまで暫定
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
