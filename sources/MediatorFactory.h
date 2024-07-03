#pragma once
#include <memory>
class MediatorBase;

/// <summary>
/// mediator生成をspawner側で簡単にできるように、各キャラごとの生成メソッドを分離する形に…
/// </summary>
class MediatorFactory {
public:
    virtual ~MediatorFactory() = default;
    /// <summary>
    /// 各mediatorごとに対応できる関数を定義する。
    /// 以下をマネする形になる…テンプレートでうまくできればいいんだけど
    /// std::unique_ptr<StateMediator> createMediator() override 
    /// {   return std::make_unique<DefensiveMediator>();   }
    /// </summary>
    /// <returns></returns>
    virtual std::unique_ptr<MediatorBase> createMediator() = 0;
};

