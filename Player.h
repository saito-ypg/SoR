#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    int hModel_;
    //入れたベクトルをスクリーン座標からワールド座標に変換して返す
    XMVECTOR GetMouseTargetPos(XMFLOAT3 mouse);
    
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};