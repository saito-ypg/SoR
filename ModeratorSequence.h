#pragma once
#include "Engine\GameObject.h"
/// <summary>
/// �Q�[���̐i�s�������ǂ�
/// �G�𒼐ڃV�[���ɏo���̂ł͂Ȃ��A��������w�߂��o���ē���̃^�C�~���O�ŏo���`�Ƃ���
/// ���̑�UI�Ƃ���Scene��?
/// �������e����
/// </summary>
class ModeratorSequence :
    public GameObject
{
private:
    float time;//���͏������Ԉˑ�����Ȃ��t���[�����ˑ�������A���ԑ��₷�̂��Œ�ł�����
    

public:
    ModeratorSequence(GameObject*parent);
    ~ModeratorSequence();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
};

