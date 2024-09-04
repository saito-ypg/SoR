#pragma once
/// <summary>
/// GameObject�̈ꎞ�I�������͍P�v�I�ȑ��x�ω��̎w�߂��s���B
/// 
/// </summary>

class GameObject;
struct TempSpeedModifier {
	GameObject*  object;//�K���Ώۂ̃|�C���^
	float speedMultiplier;//���x�{��
	float duration;//�p�����ԁA�~���b
};
class TimeScaleManager
{
	TimeScaleManager() = default;
	~TimeScaleManager() = default;
	TimeScaleManager(const TimeScaleManager&) = delete;
	TimeScaleManager& operator=(const TimeScaleManager&) = delete;
public:

	static TimeScaleManager& getInstance()
	{
		static TimeScaleManager instance;
		return instance;
	}
	/// <summary>
	/// �ꎞ�I�ȑ��x�̕ω��̂��̂̎��Ԃ��X�V�A�߂�����߂��č폜����
	/// </summary>
	/// <param name="dt"></param>
	void Update(const float& dt);

	/// <summary>
	/// �ꎞ�I�ȑ��x�̕ω���ݒ肷��
	/// </summary>
	/// <param name="mod"></param>
	void SetTemporarySpeedModifier(TempSpeedModifier &&mod);
	/// <summary>
	/// �ꎞ�I�ȑ��x�ω���ݒ肷��
	/// </summary>
	/// <param name="obj">�ݒ�Ώۂ�GameObject</param>
	/// <param name="multiplier">�{���A��{1</param>
	/// <param name="duration">�{����K�p�����鎞�ԁA�~���b</param>
	void SetTemporarySpeedModifier(GameObject* obj, float multiplier, float duration);
};

