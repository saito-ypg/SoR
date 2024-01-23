#include<vector>
#include "HPBar.h"
#include"Engine/Image.h"
#include"Engine/Camera.h"
namespace {
	
	using std::vector;
	vector<int>hImage((int) HPBar::HANDLE::NUM);
}

void HPBar::Initialize()
{
	for (auto &i : hImage)
	{
		i =-1;
	}
	hImage.at(BASE) = Image::Load("Assets/Interface/gaugeBack.png");
	hImage.at(DMG) = Image::Load("Assets/Interface/gaugeDamaged.png");
	hImage.at(BAR) = Image::Load("Assets/Interface/gaugeBar.png");
	hImage.at(FRAME) = Image::Load("Assets/Interface/gaugeFrame.png");
	for (const auto& i : hImage) {
		assert(i>=0);
	}
}

void HPBar::Update(float hp)
{
}

void HPBar::Draw(HANDLE h,Transform t)
{
	Image::SetTransform(hImage.at((int)h), t);
	Image::Draw(hImage.at((int)h));
}
