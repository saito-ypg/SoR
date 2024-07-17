#include "RegistrationFactory.h"
#include"MediatorFactoryRegistry.h"
#include"EnemyType.h"
#include"DecoyMediator.h"
#include"SoldierMediator.h"
using std::make_unique;
void RegistrationFactory::RegisterAllFactory()
{
	if (!MediatorFactoryRegistry::IsInitialized()) {
		//�ȉ��ɓG���Ƃ�mediator�𑝂₵�Ă���
		MediatorFactoryRegistry::RegisterFactory(EnemyType::DECOY, make_unique<DecoyMediatorFactory>());
		MediatorFactoryRegistry::RegisterFactory(EnemyType::SOLDIER, make_unique<SoldierMediatorFactory>());
	
	
		
	}
}
