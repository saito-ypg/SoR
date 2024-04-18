#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
#include"PlayerSkillsInclude.h"
constexpr float MOVE_VELOCITY = 10.0f /60;
class Player : public GameActor
{//Pimplとかいう概念、よさそう
    int hModel_;
    //移動方向の単位ベクトルを格納
    XMVECTOR moveDirection_;
    //移動ベクトル
    XMVECTOR vMove_;
    //移動にかかるフレーム数を入れる。移動中断したら0に
    float moveTime_;

 //スキル登録
    const int skillsNum = 1;
    std::vector<SkillBase*>skills{ static_cast<size_t>(skillsNum)};
    //bool isSkillUsing;
    int usingSkillIndex;
    bool canUseSkill(int number);
    void ActivateSkill(int number);
    
    //現在のマウス座標をワールド座標に変換して返す
    XMVECTOR getMouseTargetPos();
    //targetの方向に回転
    void FaceTargetDirection(const XMVECTOR& target_);
    //移動+回転
    void calculateForMove(const XMVECTOR target_);
    
    void FaceMouseDirection();

    void move();
    
    void AddCamp()override;
    void RemoveCamp()override;
#ifdef _DEBUG
    //test
    AttackRangeQuad testQuad;
    AttackRangeCircle testCircle;
    AttackRangeCirculerSector testSector;
#endif // _DEBUG

    bool isDuringSkill();
    void MoveInput();
protected:
    void dyingProcess()override;
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    virtual ~Player();

    //初期化
    void Initialize() override;

    //個別更新
    void ActorUpdate(const float& dt) override;



   

    bool isIntersectGround(const DirectX::XMVECTOR& target);

    //描画
    void ActorDraw() override;

    //開放
    void Release() override;

};