#pragma once
#include "SkillBase.h"

/// <summary>
/// ���̃X�L���B����ł͉~�`�ɍU���͈͂��o���B
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

