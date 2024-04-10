#pragma once
#include "SkillBase.h"
class testSkill :
    public SkillBase
{
private:
 
    AttackRangeCircle circle;
 
public:
    testSkill();
    ~testSkill();

    void action()override;
    void Draw() override;
    void Release() override;
    void DrawRangeDisplay(Transform tr) override;
};

