#include "PlayerInterface.h"
#include"../Engine/Image.h"
constexpr float SKILL_ALIGN_UNDER=680;
PlayerInterface::PlayerInterface(GameObject* parent) :GameObject(parent, "PlayerInterface"), pPlayer(nullptr)
{
}

PlayerInterface::~PlayerInterface()
{
}

void PlayerInterface::SetPlayer(Player* p)
{
	assert(p != nullptr);
	pPlayer = p;

}

void PlayerInterface::Initialize()
{
	hModels.emplace("uiback",Image::Load(ASSET_PATH + "Interface/UIBack.png"));
	hModels.emplace("spinicon", Image::Load(ASSET_PATH + "Interface/spinicon.png"));
	for (const auto& itr : hModels)
	{
		assert(itr.second >= 0);
	}

}

void PlayerInterface::Update(const float& dt)
{
	if (!pPlayer)
		return;
}

void PlayerInterface::Draw()
{
	if (!pPlayer)
		return;

	Transform BackTransform;
	BackTransform.scale_.x = 3.5f;
	const int& back = hModels.at("uiback");
	BackTransform.position_.y = Image::AlignImage(back, DOWN);
	Image::SetTransform(back, BackTransform);
	
	Transform spinT;
	const int& spinskill = hModels.at("spinicon");
	spinT.position_ = Image::toPos(XMFLOAT3(400, Image::AlignImage(spinskill,DOWN,SKILL_ALIGN_UNDER), 0));

	for (const auto&[name,handle] : hModels)//àÍêƒï`âÊ
	{
		Image::Draw(handle);
	}

}

void PlayerInterface::Release()
{
}
