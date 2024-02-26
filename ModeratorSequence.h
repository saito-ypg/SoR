#pragma once
#include<chrono>
#include<map>
#include "Engine\GameObject.h"
#include"EnemyType.h"
/// <summary>
/// ゲームの進行をつかさどる
/// 敵を直接シーンに出すのではなく、此処から指令を出して特定のタイミングで出現～とする
/// その他UIとかはSceneに?
/// 処理内容未定
/// </summary>

class EnemyManager;
class EnemySpawner;
using std::chrono::milliseconds;
class ModeratorSequence :
    public GameObject
{

private:
    milliseconds curTime;//今は処理時間依存じゃなくフレーム数依存だから、時間増やすのも固定でいいか
    milliseconds ttlTime;//ゲーム全体
    int waves;//ウェーブ数
    EnemyManager* manager;
    enum {
        CHANGED=0,//シーン変わった直後
        PREP,//準備
        BEGIN,//敵スポーン開始
        END//敵全滅後
    } state;//
    const std::map<std::string, EnemyType> TypeMap =
    {
        {"DECOY",EnemyType::DECOY}
    };
    struct Stage
    {
        float spawntime;//ウェーブ開始後スポーンする時間（秒)
        string enemytype;
        bool is_boss;

    };

    void LoadData();
public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;
};

