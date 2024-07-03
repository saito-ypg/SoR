#pragma once
#include <memory>
class MediatorBase;

/// <summary>
/// mediator������spawner���ŊȒP�ɂł���悤�ɁA�e�L�������Ƃ̐������\�b�h�𕪗�����`�Ɂc
/// </summary>
class MediatorFactory {
public:
    virtual ~MediatorFactory() = default;
    /// <summary>
    /// �emediator���ƂɑΉ��ł���֐����`����B
    /// �ȉ����}�l����`�ɂȂ�c�e���v���[�g�ł��܂��ł���΂����񂾂���
    /// std::unique_ptr<StateMediator> createMediator() override 
    /// {   return std::make_unique<DefensiveMediator>();   }
    /// </summary>
    /// <returns></returns>
    virtual std::unique_ptr<MediatorBase> createMediator() = 0;
};

