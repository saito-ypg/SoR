#pragma once
#include"SkillBase.h"

/// <summary>
///�v���C���[���ːi���s���X�L���B�c���̋�`�͈̔͂ɍU��������B�ːi�����邽�߁A�傫���O�ɓ��ݍ��ށB
/// �ːi���͖��G�B
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

