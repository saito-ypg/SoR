#pragma once
#include <memory>
class MediatorBase;
class EnemyBase;
/// <summary>
/// Mediator生成をSpawner側で簡単にできるように、各キャラごとの生成メソッドを分離する形に…
/// </summary>
class MediatorFactory {
public:
    virtual ~MediatorFactory() = default;
    /// <summary>
    /// 各Mediatorごとに対応できる関数を定義する。
    /// 以下をマネする形になる…テンプレートでうまくできればいいんだけど
    /// std::unique_ptr<MediatorBase> createMediator() override 
    /// {   return std::make_unique<○○Mediator>();   }
    /// </summary>
    /// <returns></returns>
    virtual std::unique_ptr<MediatorBase> createMediator(EnemyBase&enemy) = 0;
};

