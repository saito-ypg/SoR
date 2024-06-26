#pragma once
#include<vector>
#include "../Engine/GameObject.h"
#include"../Engine/Text.h"
class Player;
class SkillBase;
/// <summary>
/// �v���C���[�̏�����ʂɕ\������B
/// �V�[�������ɒu��
/// </summary>
class PlayerInterface :
    public GameObject
{
    Text *pText;
    Player* pPlayer;
    int hImageBack;
    int hImageCD;
    int hImageActive;
    bool isPlayerHiddenInUI;
    std::vector<int> hSkillIcons;
    std::vector<SkillBase*>skillList;//�v���C���[������炤
    void loadAndPush(std::string path);
public:
    PlayerInterface(GameObject* parent);
    ~PlayerInterface();

    void SetPlayer(Player* const p);
    void Initialize()override;
  
    void Update(const float& dt)override;
    void Draw()override;
    void HideUIHandle(int handle) const;
    void DrawSkillIcon();
    void Release()override;
};

