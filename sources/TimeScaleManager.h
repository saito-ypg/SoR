#pragma once
/// <summary>
/// GameObjectの一時的もしくは恒久的な速度変化の指令を行う。
/// 
/// </summary>

class GameObject;
struct SpeedModifier {
	GameObject* const object;//適応対象のポインタ
	float speedMultiplier;//速度倍率
	float duration;//継続時間、ミリ秒
};
class TimeScaleManager
{
public:
	TimeScaleManager();
	/// <summary>
	/// 一時的な速度の変化のものの時間を更新、過ぎたら戻して削除する
	/// </summary>
	/// <param name="dt"></param>
	void Update(const float& dt);

	/// <summary>
	/// 一時的な速度の変化を設定する
	/// </summary>
	/// <param name="mod"></param>
	void SetSpeedModifier(SpeedModifier &&mod);
	/// <summary>
	/// 一時的な速度変化を設定する
	/// </summary>
	/// <param name="obj">設定対象のGameObject</param>
	/// <param name="multiplier">倍率、基本1</param>
	/// <param name="duration">倍率を適用させる時間、ミリ秒</param>
	void SetSpeedModifier(GameObject* obj, float multiplier, float duration);
};

