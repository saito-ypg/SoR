#pragma once
#include"SkillBase.h"

/// <summary>
///プレイヤーが突進を行うスキル。縦長の矩形の範囲に攻撃をする。突進をするため、大きく前に踏み込む。
/// 突進中は無敵。
/// </summary>

class ChargeSkill :
    public SkillBase
{
private:
    AttackRangeQuad QuadArea;

public:
    ChargeSkill(Player*pPlayer);
    virtual ~ChargeSkill();
    void action()override;
    void Draw() override;
    void DrawRangeDisplay() override;
    void Release() override;
 
};

