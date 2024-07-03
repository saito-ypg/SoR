#pragma once
#include <memory>
class MediatorBase
class MediatorFactory {
public:
    virtual ~MediatorFactory() = default;
    virtual std::unique_ptr<MediatorBase> createMediator() = 0;
};

