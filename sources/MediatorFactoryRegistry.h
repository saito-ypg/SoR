// MediatorFactoryRegistry.hpp
#include <string>
#include <unordered_map>
#include <memory>
class MediatorFactory;
enum class EnemyType;

/// <summary>
/// spawnerでmediatorを簡単に注入できるように、ファクトリを登録/呼び出しできるクラス
/// 
/// </summary>
class MediatorFactoryRegistry {
private:
    static std::unordered_map<EnemyType, std::unique_ptr<MediatorFactory>> factories;
    static bool isInitialized;

public:
    static void RegisterFactory(const EnemyType type, std::unique_ptr<MediatorFactory> factory);
    static MediatorFactory* getFactory(const EnemyType type);
    static bool IsInitialized();
};

