#pragma once
#include<map>
#include "../Engine/GameObject.h"

class Player;
/// <summary>
/// �v���C���[�̏�����ʂɕ\������B
/// �V�[�������ɒu��
/// </summary>
class PlayerInterface :
    public GameObject
{
    Player* pPlayer;
    std::map<std::string,int> hModels;
public:
    PlayerInterface(GameObject*parent);
    ~PlayerInterface();

    void SetPlayer(Player* p);
    void Initialize()override;
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;
};

