#include "PlayerInterface.h"
#include<array>
#include"../Engine/Image.h"
#include"../Engine/Camera.h"
#include"Player.h"
#include"SkillBase.h"

#define RETURN_IF_PLAYER_ISNT_EXIST {if(!pPlayer){return;}}
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
	isPlayerHiddenInUI = false;
}

PlayerInterface::~PlayerInterface()
{
}

void PlayerInterface::SetPlayer(Player* const p)
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
	pPlayer =dynamic_cast<Player*>(FindObject("Player"));
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
	RETURN_IF_PLAYER_ISNT_EXIST;
}

void PlayerInterface::Draw()
{
	RETURN_IF_PLAYER_ISNT_EXIST;



	Transform BackT;
	BackT.scale_.x = 4.5f;
	BackT.position_.y=Image::toPos(XMFLOAT3(0,Image::AlignImage(hImageBack, DOWN),0)).y;
	Image::SetTransform(hImageBack, BackT);
	isPlayerHiddenInUI =Image::isPointInside(hImageBack,BackT, Image::toPixel(Camera::convertWorldToNDC(*pPlayer->GetTransformRef())));
	TransparentizeIfPlayerBehind(hImageBack);
	Image::Draw(hImageBack);
	DrawSkillIcons();


}
static constexpr int calcAlphaMax255(float percentage) {
	if (percentage < 0 || percentage>100) {
		return 255;
	}
	return static_cast<int>(255 * percentage*0.01);
}
void PlayerInterface::TransparentizeIfPlayerBehind(int handle) const
{
	constexpr int	OPAQUE_ALPHA = calcAlphaMax255(100),//不透明な値
					TRANSLUCENT_ALPHA = calcAlphaMax255(40);
	if (isPlayerHiddenInUI) {
		Image::SetAlpha(handle, TRANSLUCENT_ALPHA);
	}
	else{
		Image::SetAlpha(handle, OPAQUE_ALPHA);
	}
}

void PlayerInterface::DrawSkillIcons()
{
	std::vector<float>vSkillCD;
	
	for (int i = 0,end = static_cast<int>(skillList.size()); i < end;i++) {
		const auto& it = skillList.at(i);
		if (!it)
			continue;
		vSkillCD.push_back(it->getCdPercentage());
		if (it->IsInOperation()) {
			index = i;
		}
	}
	const std::vector<std::string>inputKey = { "Q","W"};//いずれarrayにする
	for (int i = 0; i < hSkillIcons.size(); i++){
		Transform PictT;
		const int& handle = hSkillIcons.at(i);
		PictT.position_ = Image::toPos(XMFLOAT3(ICON_LEFT + ICON_DIST * i, Image::AlignImage(handle, DOWN, SKILL_ALIGN_UNDER), 0));
		if (i == index) {//使用中スキルなら

			DrawCT(i, PictT);
		}
		DrawIcon(handle, PictT);

		//CDあれば暗いのかぶせる
		DrawCD(vSkillCD.at(i), PictT);

		if (Image::isMouseOver(handle,PictT)) {//フローティングメニューとか出してみたい
			DrawSkillTips(i,PictT );
		}
		pText->Draw(static_cast<int>(ICON_LEFT + ICON_DIST * i), static_cast<int>(SKILL_ALIGN_UNDER)+16,inputKey.at(i).c_str());
	}
	
}

void PlayerInterface::DrawSkillTips(const float& cd,Transform& PictT)
{
	XMFLOAT3 pixelPos = Image::toPixel(PictT.position_);
	pText->DrawCenter((int)pixelPos.x, (int)pixelPos.y, "tipToDo");
}

void PlayerInterface::DrawCD(const float& cd, const Transform& PictT)
{
	if (cd <= 1.0f) {
		Transform grayT = PictT;
		grayT.scale_.y = cd;
		grayT.position_.y = Image::toPos(Image::AlignImage(hImageCD, DOWN, SKILL_ALIGN_UNDER, grayT.scale_.y), Y);
		Image::SetTransform(hImageCD, grayT);
		Image::SetAlpha(hImageCD, 0xB2);
		Image::Draw(hImageCD);
	}
}

void PlayerInterface::DrawIcon(const int& handle, Transform& PictT) const
{
	TransparentizeIfPlayerBehind(handle);
	Image::SetTransform(handle, PictT);
	Image::Draw(handle);
}

void PlayerInterface::DrawCT(int i, const Transform& PictT)
{
	const float castTimePercentage = skillList.at(i)->getCtPercentage();
	if (castTimePercentage > 0)//割合は時間に応じて1〜0で帰ってくる。
	{
		constexpr float testImagesize = 64.0f / 70.0f;//画像サイズ調整中
		Transform activeT = PictT;
		activeT.scale_.y = castTimePercentage * testImagesize;
		activeT.position_.y = Image::toPos(Image::AlignImage(hImageActive, DOWN, SKILL_ALIGN_UNDER, activeT.scale_.y), Y);
		TransparentizeIfPlayerBehind(hImageActive);
		Image::SetTransform(hImageActive, activeT);
		Image::Draw(hImageActive);
	}
	else {
		index = pPlayer->UNUSED;
	}
}

void PlayerInterface::Release()
{
}
