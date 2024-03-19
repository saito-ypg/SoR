#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class Ground : public GameObject
{
    int hModel_;
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
    
    int GetGloundHandle();
};