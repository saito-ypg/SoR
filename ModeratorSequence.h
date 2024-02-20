#pragma once
#include<chrono>
#include "Engine\GameObject.h"

/// <summary>
/// �Q�[���̐i�s�������ǂ�
/// �G�𒼐ڃV�[���ɏo���̂ł͂Ȃ��A��������w�߂��o���ē���̃^�C�~���O�ŏo���`�Ƃ���
/// ���̑�UI�Ƃ���Scene��?
/// �������e����
/// </summary>

class EnemyManager;
class EnemySpawner;
using std::chrono::milliseconds;
class ModeratorSequence :
    public GameObject
{

private:
    milliseconds curTime;//���͏������Ԉˑ�����Ȃ��t���[�����ˑ�������A���ԑ��₷�̂��Œ�ł�����
    milliseconds ttlTime;//�Q�[���S��
    int waves;//�E�F�[�u��
    EnemyManager* manager;
    enum {
        PREP=0,//����
        BEGIN,//�G�X�|�[���J�n
        END//�G�S�Ō�
    } state;//
public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;
};

