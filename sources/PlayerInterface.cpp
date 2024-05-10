#include "PlayerInterface.h"
#include"../Engine/Image.h"
#include"Player.h"
enum eImage{
	SKILL_SPIN,
	SKILL_CHARGE
};
namespace {
	//定数
	constexpr float SKILL_ALIGN_UNDER = 680;
	constexpr float ICON_DIST = 80;
	constexpr float ICON_LEFT = 400;
}
PlayerInterface::PlayerInterface(GameObject* parent) :GameObject(parent, "PlayerInterface")
{
	hImageBack = -1;
}

PlayerInterface::~PlayerInterface()
{
}

void PlayerInterface::SetPlayer(const Player* const p)
{
	assert(p != nullptr);
	pPlayer = p;

}

void PlayerInterface::Initialize()
{
	hImageBack = Image::Load(ASSET_PATH + "Interface/UIBack.png");
	assert(hImageBack >= 0);
	loadAndPush("spinicon.png");
	loadAndPush("charge.png");


	loadAndPush("iconCD.png");//これは最後尾
	for (const auto& itr : hSkillIcons)
	{
		assert(itr >= 0);
	}

}

void PlayerInterface::loadAndPush(std::string path)
{
	hSkillIcons.emplace_back(Image::Load(ASSET_PATH +"Interface/"+ path));
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
	BackTransform.scale_.x = 4.5f;
	BackTransform.position_.y=Image::toPos(XMFLOAT3(0,Image::AlignImage(hImageBack, DOWN),0)).y;
	Image::SetTransform(hImageBack, BackTransform);
	Image::Draw(hImageBack);
	
}

void PlayerInterface::DrawSkillIcon()
{
	std::vector<float>v = pPlayer->getSkillPercentageVec();
	const int& cdGrayQuad = v.size() - 1;//アイコンの上にかぶせる暗いやつ

	for (int i = 0; i < cdGrayQuad; i++)
	{
		//以下はループで回せるように抽象化すべき？
		Transform transform;
		const int& handle = hSkillIcons.at(i);
		transform.position_ = Image::toPos(XMFLOAT3(ICON_LEFT + ICON_DIST * i, Image::AlignImage(handle, DOWN, SKILL_ALIGN_UNDER), 0));
		transform.scale_.y = v.at(i);
		Image::SetTransform(handle, transform);
		Image::Draw(handle);

		//ここからCDあればかぶせる
	}
}

void PlayerInterface::Release()
{
}
