#pragma once
#include <memory>
class MediatorBase;
class EnemyBase;
/// <summary>
/// Mediator������Spawner���ŊȒP�ɂł���悤�ɁA�e�L�������Ƃ̐������\�b�h�𕪗�����`�Ɂc
/// </summary>
class MediatorFactory {
public:
    virtual ~MediatorFactory() = default;
    /// <summary>
    /// �eMediator���ƂɑΉ��ł���֐����`����B
    /// �ȉ����}�l����`�ɂȂ�c�e���v���[�g�ł��܂��ł���΂����񂾂���
    /// std::unique_ptr<MediatorBase> createMediator() override 
    /// {   return std::make_unique<����Mediator>();   }
    /// </summary>
    /// <returns></returns>
    virtual std::unique_ptr<MediatorBase> createMediator(EnemyBase&enemy) = 0;
};

