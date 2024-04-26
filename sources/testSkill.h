#pragma once
#include "SkillBase.h"

/// <summary>
/// 仮のスキル。現状では円形に攻撃範囲を出す。
/// </summary>
class testSkill :
    public SkillBase
{
private:


    void invokedStep() override;
    void startStep() override;
    void endStep()override;
public:
    testSkill(Player *pPlayer);
    virtual ~testSkill();

    void action()override;
    void Draw() override;
    void Release() override;
    void DrawRangeDisplay(float deg) override;
};

