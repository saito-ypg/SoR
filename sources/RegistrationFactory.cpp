#include "RegistrationFactory.h"
#include"MediatorFactoryRegistry.h"
#include"EnemyType.h"
#include"DecoyMediator.h"
#include"SoldierMediator.h"
using std::make_unique;
void RegistrationFactory::RegisterAllFactory()
{
	if (!MediatorFactoryRegistry::IsInitialized()) {
		//à»â∫Ç…ìGÇ≤Ç∆ÇÃmediatorÇëùÇ‚ÇµÇƒÇ¢Ç≠
		MediatorFactoryRegistry::RegisterFactory(EnemyType::DECOY, make_unique<DecoyMediatorFactory>());
		MediatorFactoryRegistry::RegisterFactory(EnemyType::SOLDIER, make_unique<SoldierMediatorFactory>());
	
	
		
	}
}
