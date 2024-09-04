#include "TimeScaleManager.h"
#include<vector>
#include"../Engine/GameObject.h"
using std::vector;
namespace {
	constexpr float PERMANENT_DURATION = -1;

	vector<SpeedModifier>  modifiers;
}


void TimeScaleManager::Update(const float& dt)
{
	if (modifiers.empty()) {
		return;
	}
	for (auto& itr : modifiers) {
		auto& [obj, mul, dur] = itr;
		dur -= dt;
		if (dur <= 0) {
			if (std::find_if(modifiers.begin(), modifiers.end(), [&](SpeedModifier mod) { return (&mod != &itr) && mod.object == obj; })!=modifiers.end())
			{//これ以外の要素で、同じオブジェクトに対する速度変化がないなら
				const float curObjSpeed = obj->GetMyTimeScale();
				obj->SetTimeScale(curObjSpeed / mul);
			}
			else {
				obj->SetTimeScale(1.0f);
			}

		}
	}
	std::erase_if(modifiers, [&](const SpeedModifier it) {return it.duration <= 0; });
}

void TimeScaleManager::SetSpeedModifier(SpeedModifier&& mod)
{	
	auto& [obj, multi, UNUSED] = mod;//unusedは構造化束縛の巻き添え。この中では使わないduration
	obj->SetTimeScale(obj->GetMyTimeScale() * multi);
	modifiers.push_back(std::move(mod));
}

void TimeScaleManager::SetSpeedModifier(GameObject* const obj, float multiplier, float duration)
{
	SetSpeedModifier(SpeedModifier(obj, multiplier, duration));
}
