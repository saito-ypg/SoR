#include "TimeScaleManager.h"
#include<vector>
#include"../Engine/GameObject.h"
using std::vector;
namespace {
	constexpr float PERMANENT_DURATION = -1;

	vector<TempSpeedModifier>  modifiers;
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
			if (std::find_if(modifiers.begin(), modifiers.end(), [&](TempSpeedModifier mod) { return (&mod != &itr) && mod.object == obj; })!=modifiers.end())
			{//����ȊO�̗v�f�ŁA�����I�u�W�F�N�g�ɑ΂��鑬�x�ω����Ȃ��Ȃ�
				const float curObjSpeed = obj->GetMyTimeScale();
				obj->SetTimeScale(curObjSpeed / mul);
			}
			else {
				obj->SetTimeScale(1.0f);//�덷�l����1�ɐݒ�
			}

		}
	}
	std::erase_if(modifiers, [&](const TempSpeedModifier it) {return it.duration <= 0; });
}

void TimeScaleManager::SetTemporarySpeedModifier(TempSpeedModifier&& mod)
{	
	auto& [obj, multi, UNUSED] = mod;//unused�͍\���������̊����Y���B���̒��ł͎g��Ȃ�duration
	obj->SetTimeScale(obj->GetMyTimeScale() * multi);
	modifiers.push_back(std::move(mod));
}

void TimeScaleManager::SetTemporarySpeedModifier(GameObject* const obj, float multiplier, float duration)
{
	SetTemporarySpeedModifier(TempSpeedModifier(obj, multiplier, duration));
}
