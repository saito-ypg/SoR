#include "PlayerInterface.h"
#include"../Engine/Image.h"

enum eImage{
	BACK,
	SKILL_SPIN,
	SKILL_CHARGE
};
PlayerInterface::PlayerInterface(GameObject* parent) :GameObject(parent, "PlayerInterface")
{
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
	loadAndPush("UIBack.png");
	loadAndPush("spinicon.png");
	loadAndPush("charge.png");
	for (const auto& itr : hImages)
	{
		assert(itr >= 0);
	}

}

void PlayerInterface::loadAndPush(std::string path)
{
	hImages.emplace_back(Image::Load(ASSET_PATH +"Interface/"+ path));
}

void PlayerInterface::Update(const float& dt)
{
	if (!pPlayer)
		return;
}

void PlayerInterface::Draw()
{
	//íËêî
	constexpr float SKILL_ALIGN_UNDER = 680;
	constexpr float ICON_DIST = 80;
	constexpr float ICON_LEFT = 400;

	if (!pPlayer)
		return;

	Transform BackTransform;
	BackTransform.scale_.x = 4.5f;
	const int& back = hImages.at(BACK);
	BackTransform.position_.y=Image::toPos(XMFLOAT3(0,Image::AlignImage(back, DOWN),0)).y;
	Image::SetTransform(back, BackTransform);
	
	//à»â∫ÇÕÉãÅ[ÉvÇ≈âÒÇπÇÈÇÊÇ§Ç…íäè€âªÇ∑Ç◊Ç´ÅH
	Transform spinT;
	const int& spinskill = hImages.at(SKILL_SPIN);
	spinT.position_ = Image::toPos(XMFLOAT3(ICON_LEFT+ICON_DIST*0, Image::AlignImage(spinskill,DOWN,SKILL_ALIGN_UNDER), 0));
	Image::SetTransform(spinskill, spinT);

	Transform chargeT;
	const int& chargeskill = hImages.at(SKILL_CHARGE);
	chargeT.position_ = Image::toPos(XMFLOAT3(ICON_LEFT + ICON_DIST * 1, Image::AlignImage(chargeskill, DOWN, SKILL_ALIGN_UNDER), 0));
	Image::SetTransform(chargeskill, chargeT);
	for (const auto& handle: hImages)//àÍêƒï`âÊ
	{
		Image::Draw(handle);
	}

}

void PlayerInterface::Release()
{
}
