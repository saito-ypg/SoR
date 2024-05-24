#include "PlayerInterface.h"
#include"../Engine/Image.h"
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
	
	//
	int index = Player::UNUSED;
}
PlayerInterface::PlayerInterface(GameObject* parent) :GameObject(parent, "PlayerInterface")
{
	hImageBack = -1;
	hImageCD = -1;
	hImageActive = -1;
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
	hImageActive = Image::Load(ASSET_PATH + "Interface/skillActive.png");
	pPlayer =dynamic_cast<const Player*>(FindObject("Player"));
	assert(pPlayer);

	skillList=std::move(pPlayer->getSkills());
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
	std::vector<float>vSkillCD;
	
	float castTimePercentage = 0;
	for (int i = 0,end = static_cast<int>(skillList.size()); i < end;i++) {
		const auto& it = skillList.at(i);
		if (!it)
			continue;
		vSkillCD.push_back(it->getCdPercentage());
		if (it->IsInOperation()) {
			index = i;
		}
	}
	const std::vector<std::string>inputKey = { "Q","W"};
	for (int i = 0; i < hSkillIcons.size(); i++)
	{
		Transform PictT;
		const int& handle = hSkillIcons.at(i);
		PictT.position_ = Image::toPos(XMFLOAT3(ICON_LEFT + ICON_DIST * i, Image::AlignImage(handle, DOWN, SKILL_ALIGN_UNDER), 0));
		if (i == index) {//使用中スキルなら

			castTimePercentage =skillList.at(i)->getCtPercentage();
			if (castTimePercentage >0)//割合は時間に応じて1～0で帰ってくる。
			{
				constexpr float testImagesize=64.0f/70.0f;//画像サイズ調整中
				Transform activeT = PictT;
				activeT.scale_.y = castTimePercentage * testImagesize;
				activeT.position_.y =Image::toPos(Image::AlignImage(hImageActive, DOWN, SKILL_ALIGN_UNDER, activeT.scale_.y),Y);
				Image::SetTransform(hImageActive, activeT);
				Image::Draw(hImageActive);
			}
			else
				index = pPlayer->UNUSED;
		}
		Image::SetTransform(handle, PictT);
		Image::Draw(handle);

		//CDあれば暗いのかぶせる
		if (vSkillCD.at(i) <= 1.0f) {
			Transform grayT = PictT;
			grayT.scale_.y = vSkillCD.at(i);
			grayT.position_.y = Image::toPos(Image::AlignImage(hImageCD, DOWN, SKILL_ALIGN_UNDER, grayT.scale_.y), Y);
			Image::SetTransform(hImageCD, grayT);
			Image::SetAlpha(hImageCD, 0xB2);
			Image::Draw(hImageCD);
		}

		if (Image::isMouseOver(handle)) {//フローティングメニューとか出してみたい
			XMFLOAT3 pixelPos=Image::toPixel(PictT.position_);
			pText->DrawCenter((int)pixelPos.x,(int)pixelPos.y, "tip");
		}
		pText->Draw(static_cast<int>(ICON_LEFT + ICON_DIST * i), static_cast<int>(SKILL_ALIGN_UNDER)+16,inputKey.at(i).c_str());
	}
	
}

void PlayerInterface::Release()
{
}
