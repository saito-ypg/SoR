#pragma once
#include "Engine\GameObject.h"
/// <summary>
/// ゲームの進行をつかさどる
/// 敵を直接シーンに出すのではなく、此処から指令を出して特定のタイミングで出現〜とする
/// その他UIとかはSceneに?
/// 処理内容未定
/// </summary>
class ModeratorSequence :
    public GameObject
{
private:
    float time;//今は処理時間依存じゃなくフレーム数依存だから、時間増やすのも固定でいいか
    

public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
};

