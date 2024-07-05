#include "MediatorFactoryRegistry.h"
#include"MediatorFactory.h"
#include"EnemyType.h"
std::unordered_map<EnemyType, std::unique_ptr<MediatorFactory>> MediatorFactoryRegistry::factories;

void MediatorFactoryRegistry::RegisterFactory(const EnemyType type, std::unique_ptr<MediatorFactory> &&factory)
{
	factories.try_emplace(type,std::move(factory));
}


MediatorFactory* MediatorFactoryRegistry::getFactory(const EnemyType type)
{
	if(!isInitialized)
	{
		__debugbreak;
	}
	auto it = factories.find(type);
	return it != factories.end() ? it->second.get() : nullptr;
}

bool MediatorFactoryRegistry::IsInitialized()
{
	return isInitialized;		
}
