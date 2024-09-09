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
    //�R���X�g���N�^
    Ground(GameObject* parent);

    //�f�X�g���N�^
    ~Ground();

    //������
    void Initialize() override;

    //�X�V
    void Update(const float& dt) override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
    
};