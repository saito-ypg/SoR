#include "TimeScaleManager.h"
#include<vector>
#include"../Engine/GameObject.h"
using std::vector;
namespace {
	constexpr float PERMANENT_DURATION = -1;

	vector<SpeedModifier>  modifiers;
}

TimeScaleManager::TimeScaleManager()
{
}

void TimeScaleManager::Update(const float& dt)
{
	for (auto& itr : modifiers) {
		itr.
	}
}

void TimeScaleManager::SetSpeedModifier(SpeedModifier&& mod)
{
	modifiers.push_back(std::move(mod));
}

void TimeScaleManager::SetSpeedModifier(GameObject* obj, float multiplier, float duration)
{
	modifiers.emplace_back(SpeedModifier(obj, multiplier, duration));
}
