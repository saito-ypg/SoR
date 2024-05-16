#include "PlayerInterface.h"
#include"../Engine/Image.h"
#include"../Engine/Debug.h"
#include"../Engine/Input.h"
#include"Player.h"
#include"SkillBase.h"

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
	hImageCD = -1;
	pText = nullptr;
	pPlayer = nullptr;
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
	pPlayer =dynamic_cast<const Player*>(FindObject("Player"));
	assert(pPlayer);

	skillList=pPlayer->getSkills();
	for (const auto& skill : skillList) {
		if (skill != nullptr)
			loadAndPush(skill->getIconName());
	}
	pText = new Text;
	pText->Initialize();


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
	std::vector<float>vSkillCD = pPlayer->getCoolDownPercentageVec();
	const std::vector<std::string>inputKey = { "Q","W"};
	for (int i = 0; i < hSkillIcons.size(); i++)
	{

		Transform PictT;
		const int& handle = hSkillIcons.at(i);
		PictT.position_ = Image::toPos(XMFLOAT3(ICON_LEFT + ICON_DIST * i, Image::AlignImage(handle, DOWN, SKILL_ALIGN_UNDER), 0));
		Image::SetTransform(handle, PictT);
		Image::Draw(handle);

		//ここからCDあればかぶせる
		if (vSkillCD.at(i) <= 1.0f) {
			PictT.scale_.y = vSkillCD.at(i);
			PictT.position_.y = Image::toPos(Image::AlignImage(hImageCD, DOWN, SKILL_ALIGN_UNDER, PictT.scale_.y), Y);
			Image::SetTransform(hImageCD, PictT);
			Image::SetAlpha(hImageCD, 0xB2);
			Image::Draw(hImageCD);
		}

		if (Image::isMouseOver(handle)) {//フローティングメニューとか出してみたい

		}
		pText->Draw(static_cast<int>(ICON_LEFT + ICON_DIST * i), static_cast<int>(SKILL_ALIGN_UNDER)+16,inputKey.at(i).c_str());
	}
	
}

void PlayerInterface::Release()
{
}
