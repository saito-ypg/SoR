#pragma once
/// <summary>
/// GameObjectの一時的もしくは恒久的な速度変化の指令を行う。
/// 
/// </summary>

class GameObject;
struct SpeedModifier {
	GameObject* obj;
	float speedMultiplier;
	float duration;//継続時間、ミリ秒
};
class TimeScaleManager
{
public:
	TimeScaleManager();
	void Update(const float& dt);
	void SetSpeedModifier(SpeedModifier &&mod);
	void SetSpeedModifier(GameObject* obj, float multiplier, float duration);
};

