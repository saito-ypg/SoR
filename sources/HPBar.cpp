#include<vector>
#include"Engine/Image.h"
#include"Engine/Camera.h"
#include "HPBar.h"
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
	hImage.at(BASE)		= Image::Load("Interface/gaugeBack.png");
	hImage.at(DMG)		= Image::Load("Interface/gaugeDamaged.png");
	hImage.at(BAR)		= Image::Load("Interface/gaugeBar.png");
	hImage.at(FRAME)	= Image::Load("Interface/gaugeFrame.png");
	for (const auto& i : hImage) {
		assert(i>=0);
	}
}

void HPBar::Update(float hpRatio)
{
}

void HPBar::Draw(HANDLE h,Transform t)
{
	Image::SetTransform(hImage.at((int)h), t);
	Image::Draw(hImage.at((int)h));
}
