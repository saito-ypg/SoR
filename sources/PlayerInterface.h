#pragma once
#include<vector>
#include "../Engine/GameObject.h"
#include"../Engine/Text.h"
class Player;
/// <summary>
/// プレイヤーの情報を画面に表示する。
/// シーン直下に置く
/// </summary>
class PlayerInterface :
    public GameObject
{
    Text *pText;
    const Player* pPlayer;
    int hImageBack;
    int hImageCD;
    std::vector<int>hSkillIcons;
    std::vector<const SkillBase* const >skillList;//プレイヤーからもらう
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

