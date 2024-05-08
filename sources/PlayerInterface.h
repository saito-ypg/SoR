#pragma once
#include<vector>
#include "../Engine/GameObject.h"
class Player;
/// <summary>
/// プレイヤーの情報を画面に表示する。
/// シーン直下に置く
/// </summary>
class PlayerInterface :
    public GameObject
{
    Player* pPlayer;
    std::vector<int>hImages;
    void loadAndPush(std::string path);
public:
    PlayerInterface(GameObject*parent);
    ~PlayerInterface();

    void SetPlayer(Player* p);
    void Initialize()override;
  
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;
};

