#pragma once
#include<chrono>
#include<map>
#include "Engine\GameObject.h"
#include"EnemyType.h"
/// <summary>
/// �Q�[���̐i�s�������ǂ�
/// �G�𒼐ڃV�[���ɏo���̂ł͂Ȃ��A��������w�߂��o���ē���̃^�C�~���O�ŏo���`�Ƃ���
/// ���̑�UI�Ƃ���Scene��?
/// �������e����
/// </summary>

class EnemyManager;
class EnemySpawner;
using std::chrono::milliseconds;
using std::vector;
using std::map;
class ModeratorSequence :
    public GameObject
{

private:
    milliseconds curTime;//���͏������Ԉˑ�����Ȃ��t���[�����ˑ�������A���ԑ��₷�̂��Œ�ł�����
    milliseconds ttlTime;//�Q�[���S��
    int waves;//�E�F�[�u��
    EnemyManager* manager;
    enum {
        CHANGED=0,//�V�[���ς��������
        PREP,//����
        BEGIN,//�G�X�|�[���J�n
        END//�G�S�Ō�
    } state;//
    const std::map<std::string, EnemyType> TypeMap =
    {
        {"DECOY",EnemyType::DECOY}
    };
    struct EnemySpawning
    {
        float spawntime;//�E�F�[�u�J�n��X�|�[�����鎞�ԁi�b)
        EnemyType type;
        bool is_boss;
    };
    vector<vector<EnemySpawning>> spawnDataList;
    void LoadData();
public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;
};

