#include "PlayerInterface.h"
#include"../Engine/Image.h"
#include"Player.h"
enum eImage{
	SKILL_SPIN,
	SKILL_CHARGE
};
namespace {
	//’è”
	constexpr float SKILL_ALIGN_UNDER = 680;
	constexpr float ICON_DIST = 80;
	constexpr float ICON_LEFT = 400;
}
PlayerInterface::PlayerInterface(GameObject* parent) :GameObject(parent, "PlayerInterface")
{
	hImageBack = -1;
	hImageCD = -1;
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
	hImageCD = Image::Load(ASSET_PATH + "Interface/iconCD.png");
	assert(hImageCD >= 0);
	loadAndPush("spinicon.png");
	loadAndPush("charge.png");



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
	DrawSkillIcon();
	
}

void PlayerInterface::DrawSkillIcon()
{
	std::vector<float>vSkillCD = pPlayer->getSkillPercentageVec();

	for (int i = 0; i < hSkillIcons.size(); i++)
	{
	
		Transform PictT;
		const int& handle = hSkillIcons.at(i);
		PictT.position_ = Image::toPos(XMFLOAT3(ICON_LEFT + ICON_DIST * i, Image::AlignImage(handle, DOWN, SKILL_ALIGN_UNDER), 0));
		Image::SetTransform(handle, PictT);
		Image::Draw(handle);

		//‚±‚±‚©‚çCD‚ ‚ê‚Î‚©‚Ô‚¹‚é
		if (vSkillCD.at(i) <= 1.0f) {
			PictT.scale_.y = vSkillCD.at(i);
			PictT.position_.y = Image::toPos(Image::AlignImage(hImageCD, DOWN, SKILL_ALIGN_UNDER, PictT.scale_.y),Y);
			Image::SetTransform(hImageCD, PictT);
			Image::SetAlpha(hImageCD, 0xB2);
			Image::Draw(hImageCD);
		}
	}
}

void PlayerInterface::Release()
{
}
