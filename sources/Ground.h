#pragma once
#include "../Engine/GameObject.h"

class Ground : public GameObject
{
    int hModel_;
public:
    //コンストラクタ
    Ground(GameObject* parent);

    //デストラクタ
    ~Ground();

    //初期化
    void Initialize() override;

    //更新
    void Update(const float& dt) override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
    
    int GetGroundHandle();
};