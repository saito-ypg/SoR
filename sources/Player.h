#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
#include"PlayerSkillsInclude.h"

class Player : public GameActor
{   
public:
    static constexpr int skillsNum = 4;
    static constexpr int UNUSED = -1;//スキル長押ししてないとき
private:
    static constexpr float MOVE_VELOCITY = 10.0f /60;
    

    int usingSkillIndex = UNUSED;//使用中スキル番号、なかったらUNUSED(=-1);
    //Pimplとかいう概念、よさそう
    int hModel_;
    //移動方向の単位ベクトルを格納
    XMVECTOR moveDirection_;
    //移動ベクトル
    XMVECTOR vMove_;
    //移動にかかるフレーム数を入れる。移動中断したら0に
    float moveTime_;

 //スキル登録
 
    std::vector<SkillBase*>skills{ static_cast<size_t>(skillsNum)};   
    bool canUseSkill(int number);
    void ActivateSkill(int number);
    
    template<class skill>
    void AttachSkill(int index) {//スキルをプレイヤーに紐づける
        assert(!skills.at(index));//atで範囲外は捨てつつ登録の番号にかぶりがないようにする(被っている=インスタンス化されている)
        skills.at(index) = dynamic_cast<SkillBase*>(new skill(this));
    }

    //現在のマウス座標をワールド座標に変換して返す
    XMVECTOR getMouseTargetPos();
    //targetの方向に回転
    float GetTargetDirection(const XMVECTOR& target_) const;
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

   
    //UI用。クールダウン割合とか個別でやり取りよりこっちのほうがいい？
    std::vector<SkillBase*>getSkills() const ;
    int getUsingSkill() const { return usingSkillIndex; }


};