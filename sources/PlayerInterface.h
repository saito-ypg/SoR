#pragma once
#include<vector>
#include "../Engine/GameObject.h"
class Player;
/// <summary>
/// �v���C���[�̏�����ʂɕ\������B
/// �V�[�������ɒu��
/// </summary>
class PlayerInterface :
    public GameObject
{
    const Player* pPlayer;
    std::vector<int>hImages;
    void loadAndPush(std::string path);
public:
    PlayerInterface(GameObject* parent);
    ~PlayerInterface();

    void SetPlayer(const Player* const p);
    void Initialize()override;
  
    void Update(const float& dt)override;
    void Draw()override;
    void DrawSkillIcon();
    void Release()override;
};

