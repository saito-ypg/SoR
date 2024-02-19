#pragma once
#include "Engine\GameObject.h"
/// <summary>
/// �Q�[���̐i�s�������ǂ�
/// �G�𒼐ڃV�[���ɏo���̂ł͂Ȃ��A��������w�߂��o���ē���̃^�C�~���O�ŏo���`�Ƃ���
/// ���̑�UI�Ƃ���Scene��?
/// �������e����
/// </summary>

class EnemyManager;
class EnemySpawner;

class ModeratorSequence :
    public GameObject
{
private:
    float curTime;//���͏������Ԉˑ�����Ȃ��t���[�����ˑ�������A���ԑ��₷�̂��Œ�ł�����
    float ttlTime;//�Q�[���S��
    int waves;//�E�F�[�u��
    EnemyManager* manager;

public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
};

