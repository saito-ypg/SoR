#pragma once
#include <string>
#include <memory>
class MediatorFactoryRegistry {
public:
    static void registerFactory(const std::string& name, std::unique_ptr<MediatorFactory> factory);
    static MediatorFactory* getFactory(const std::string& name);
};