#pragma once
#include<memory>
#include"MovementStateBase.h"

class EnemyBase;
/// <summary>
/// 敵の行動パターン(state)の切り替えや管理を行うクラス
/// 敵各種ごとに定義する
/// </summary>
class MediatorBase
{
protected:
	std::unique_ptr<MovementStateBase> curState_;//現在のステート
	EnemyBase& base_ ;
	int SkipDeterminingMs;//もし判断後に遷移しなかったらこのカウントが0以下になるまで次の判断をおこなわない
	/// <summary>
	/// 次のステートの遷移先を判断する。
	/// もし同じステートならそのまま、変わっているならChangeStateを呼ぶ
	/// </summary>
	virtual void DetermineNextState() = 0;

	/// <summary>
	/// 次のステートをインスタンス化する
	/// </summary>
	template<class T>
	void ChangeState() {
		static_assert(std::is_base_of_v<MovementStateBase, T>, "ステートクラスを継承していません");
		static_assert(!std::is_abstract_v<T>, "抽象クラスです！");
		curState_ = std::make_unique<T>(base_);
	}

public:
	MediatorBase(EnemyBase& enemy);
	virtual ~MediatorBase();
	void Update(const float& dt);
	const std::type_info& getCurStateType()const;
};

