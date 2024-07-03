#include "RegistrationFactory.h"
#include"MediatorFactoryRegistry.h"
#include"EnemyType.h"
#include"DecoyMediator.h"
using std::make_unique;
void RegistrationFactory::RegisterAllFactory()
{
	if (!MediatorFactoryRegistry::IsInitialized) {
		//ˆÈ‰º‚É“G‚²‚Æ‚Ìmediator‚ğ‘‚â‚µ‚Ä‚¢‚­
		MediatorFactoryRegistry::RegisterFactory(EnemyType::DECOY, make_unique<DecoyMediatorFactory>());

	}
}
