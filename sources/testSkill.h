#pragma once
#include "SkillBase.h"
class testSkill :
    public SkillBase
{
private:
    
public:
    testSkill();
    ~testSkill();

    void action()override;
    void Draw() override;
    void Release() override;
    void DrawRangeDisplay() override;
};

