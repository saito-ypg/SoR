#pragma once
#include "SkillBase.h"
class testSkill :
    public SkillBase
{
private:
    
public:
    testSkill();
    ~testSkill();
    //void Update()override;
    void action()override;
    void Draw() override;
};

