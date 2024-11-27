#pragma once
#include "Engine/GameObject.h"
#include<vector>
class Ground : public GameObject
{
    struct StaticObject {
        int handle;
        Transform transform;
        StaticObject() = delete;
        StaticObject(int h, Transform t) :handle(h), transform(t) {};
    };

    std::vector<StaticObject>staticObjects;
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
    
};