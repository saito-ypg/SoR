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

    std::vector<int> hSkillIcons;
    std::vector<SkillBase*>skillList;//�v���C���[������炤


    void loadAndPush(std::string path);

    //void TransparentizeIfPlayerBehind(int handle) const;

    //Draw������
    void DrawSkillIcons();
    //DrawSkillIcons������ɕ���
    void DrawCT(int i, const Transform& PictT);
    void DrawIcon(const int& handle, Transform& PictT) const;
    void DrawCD(const float& cd, const Transform& PictT);
    void DrawSkillTips(Transform& PictT);
    
public:
    PlayerInterface(GameObject* parent);
    ~PlayerInterface();

    void SetPlayer(Player* const p);
    void Initialize()override;
  
    void Update(const float& dt)override;
    void Draw()override;

    void Release()override;
};

