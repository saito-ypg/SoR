#pragma once
#include "SkillBase.h"
class testSkill :
    public SkillBase
{

public:
    testSkill();
    ~testSkill();
    void Update()override;
    void action()override;
};

