#pragma once
#include<chrono>
#include<map>
#include "../Engine/GameObject.h"
#include"../Engine/Text.h"
#include"EnemyType.h"

/// <summary>
/// ゲームの進行をつかさどる
/// 敵を直接シーンに出すのではなく、此処から指令を出して特定のタイミングで出現～とする
/// その他UIとかはSceneに?
/// 処理内容未定
/// </summary>

class EnemyManager;
class EnemySpawner;
struct EnemySpawning
{
    float spawntime;//ウェーブ開始後スポーンする時間（秒)
    EnemyType type;
    bool is_boss;
    auto operator<=>(const EnemySpawning& other)const{ return this->spawntime <=> other.spawntime; }
    auto operator<=>(const float& f)const { return this->spawntime <=> f; }
    EnemySpawning() :spawntime(0), type(EnemyType::MAX), is_boss(false) {}
};
class ModeratorSequence :
    public GameObject
{

private:
    std::chrono::milliseconds curTime;//今は処理時間依存じゃなくフレーム数依存だから、時間増やすのも固定でいいか
    std::chrono::milliseconds ttlTime;//ゲーム全体
    int waves;//ウェーブ数
    int spawnindex;
    Text* pText;
    int hImage[2];
    EnemyManager* manager;
    EnemySpawner* spawner;
    enum s{
        CHANGED=0,//シーン変わった直後
        PREP,//準備
        BEGIN,//敵スポーン開始
        END,//敵全滅後
        NEXT,

        GAMEOVER,//ゲームオーバーになったら
    } state;//
    float transitionTime;//ミリ秒単位、進行に使う
    const std::map<std::string, EnemyType> TypeMap =
    {
        {"DECOY",EnemyType::DECOY}
    };
   
    std::vector<std::vector<EnemySpawning>> spawnDataList;//ウェーブ数・敵の数
    void LoadData();//jsonからデータを読む
public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;

    void SetGameOver() { state = GAMEOVER; }
};

