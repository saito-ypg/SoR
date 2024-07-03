#pragma once
#include "GameActor.h"
#include"EnemyType.h"
struct EnemyStatus {
	float hp;
	float radius;
};
class MediatorBase;
class EnemyBase : public GameActor 
{
public:
	enum SPAWINIG_STATE { WAIT, IN_SPAWN, DEAD };
private:

protected:
//�X�L������m��K�v�Ȃ�����Player�^�ɂ͂��Ȃ�
	bool isBoss_;
	GameActor* pPlayer_;
	SPAWINIG_STATE eStat_;//�Ǘ��p


	MediatorBase* pMediator_; //���̃N���X��ʂ��e�s���X�e�[�g�̊Ǘ�

	void AddCamp() override;
	void RemoveCamp() override;
	void dyingProcess()override;

	
public:
	//EnemyBase(GameObject* parent);
	EnemyBase(GameObject* parent, bool isboss = false);
	virtual ~EnemyBase();


	void SetPlayer(GameActor* p) { pPlayer_ = p; assert(pPlayer_ != nullptr); }
	void SetMediator(MediatorBase* mediator) { pMediator_ =mediator; }
	//�G�̃f�[�^��ݒ肷��
	void setConfig(EnemyStatus status);
	SPAWINIG_STATE getStat() const { return eStat_; }
	
	
};

//�G�L������pInstantiate �{�X�������܂�
//��{�I�ɂ�GameObject�̂��̂ɑ���������
template <class E, typename = std::enable_if_t<std::is_base_of_v<EnemyBase, E>>>
E* InstantiateEnemy(GameObject* pParent, bool isBoss)
{
	E* pNewObject = new E(pParent, isBoss);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}