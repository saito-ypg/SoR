#pragma once
/// <summary>
/// GameObject�̈ꎞ�I�������͍P�v�I�ȑ��x�ω��̎w�߂��s���B
/// 
/// </summary>

class GameObject;
struct SpeedModifier {
	GameObject* obj;
	float speedMultiplier;
	float duration;//�p�����ԁA�~���b
};
class TimeScaleManager
{
public:
	TimeScaleManager();
	void Update(const float& dt);
	void SetSpeedModifier(SpeedModifier &&mod);
	void SetSpeedModifier(GameObject* obj, float multiplier, float duration);
};

