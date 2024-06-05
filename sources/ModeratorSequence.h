#pragma once
#include<chrono>
#include<map>
#include "../Engine/GameObject.h"
#include"../Engine/Text.h"
#include"EnemyType.h"

/// <summary>
/// �Q�[���̐i�s�������ǂ�
/// �G�𒼐ڃV�[���ɏo���̂ł͂Ȃ��A��������w�߂��o���ē���̃^�C�~���O�ŏo���`�Ƃ���
/// ���̑�UI�Ƃ���Scene��?
/// �������e����
/// </summary>

class EnemyManager;
class EnemySpawner;
struct EnemySpawning
{
    float spawntime;//�E�F�[�u�J�n��X�|�[�����鎞�ԁi�b)
    EnemyType type;
    bool is_boss;
    auto operator<=>(const EnemySpawning& other)const{ return this->spawntime <=> other.spawntime; }
    auto operator<=>(const float& f)const { return this->spawntime <=> f; }
    EnemySpawning() :spawntime(0), type(EnemyType::MAX), is_boss(false) {}
};
class ModeratorSequence :
    public GameObject
{

private:
    std::chrono::milliseconds curTime;//���͏������Ԉˑ�����Ȃ��t���[�����ˑ�������A���ԑ��₷�̂��Œ�ł�����
    std::chrono::milliseconds ttlTime;//�Q�[���S��
    int waves;//�E�F�[�u��
    int spawnindex;
    Text* pText;
    int hImage[2];
    EnemyManager* manager;
    EnemySpawner* spawner;
    enum s{
        CHANGED=0,//�V�[���ς��������
        PREP,//����
        BEGIN,//�G�X�|�[���J�n
        END,//�G�S�Ō�
        NEXT,

        GAMEOVER,//�Q�[���I�[�o�[�ɂȂ�����
    } state;//
    float transitionTime;//�~���b�P�ʁA�i�s�Ɏg��
    const std::map<std::string, EnemyType> TypeMap =
    {
        {"DECOY",EnemyType::DECOY}
    };
   
    std::vector<std::vector<EnemySpawning>> spawnDataList;//�E�F�[�u���E�G�̐�
    void LoadData();//json����f�[�^��ǂ�
public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;

    void SetGameOver() { state = GAMEOVER; }
};

