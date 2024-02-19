#include "GameObject.h"
#include"global.h"
//#include"SphereCollider.h"

GameObject::GameObject() :pParent_(nullptr),IsDead(false)/*,pCollider_(nullptr)*/, objectName_(""),timeScale(1.0f),parentTimeScale(1.0f)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :GameObject()
{
	pParent_ = parent;
	objectName_ = name;
	if (parent)
		transform_.pParent_ = &parent->transform_;
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub(const float&  dt)
{
	
	this->Update(dt);

	for (auto it = childList_.begin(), end = childList_.end(); it != end;)
	{
		(*it)->parentTimeScale = parentTimeScale * timeScale;
		(*it)->UpdateSub(dt);
	
		if ((*it)->IsDead)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			it++;
		}
	}
	//RoundRobin(GetRootJob());
}

void GameObject::DrawSub()
{

	this->Draw();

	for (auto it = childList_.begin(), end = childList_.end(); it != end; it++)
	{

		(*it)->DrawSub();

	}

}

void GameObject::ReleaseSub()
{
	for (auto it : childList_)
	{
		(*it).ReleaseSub();
		SAFE_DELETE(it);
	}
	this->Release();

}

void GameObject::KillMe()
{
	IsDead = true;
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		return (this);
	}
	else
	{
		for (auto e : childList_)
		{
			GameObject* obj = e->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}

GameObject* GameObject::GetRootJob()
{

	if (pParent_ == nullptr)
		return this;
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}

//void GameObject::AddCollider(SphereCollider* pCollider)
//{
//	this->pCollider_ = pCollider;
//}
//
//void GameObject::Collision(GameObject* pTarget)
//{//Targetにコライダーがあるかと自分が対象になってないかのチェック、なってたら抜ける
//	if (pTarget->pCollider_ == nullptr || pTarget == this)
//	{
//		return;
//	}
//	float dist =
//		  (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x)
//		+ (transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y)
//		+ (transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
//	float rDist = (pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());
//	if(dist<=rDist)
//	{
//		OnCollision(pTarget);
//	}
//}

//void GameObject::RoundRobin(GameObject* pTarget)
//{
//	if (pCollider_ == nullptr)
//	{
//		return;
//	}
//	if (pTarget->pCollider_ != nullptr)
//		Collision(pTarget);
//	for (const auto& itr : pTarget->childList_)
//	{
//		RoundRobin(itr);
//	}
//}

