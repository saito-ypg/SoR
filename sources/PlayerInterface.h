#pragma once
#include<vector>
#include "../Engine/GameObject.h"
#include"../Engine/Text.h"
class Player;
class SkillBase;
/// <summary>
/// プレイヤーの情報を画面に表示する。
/// シーン直下に置く
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
    std::vector<SkillBase*>skillList;//プレイヤーからもらう


    void loadAndPush(std::string path);

    //void TransparentizeIfPlayerBehind(int handle) const;

    //Draw内分割
    void DrawSkillIcons();
    //DrawSkillIconsをさらに分割
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

