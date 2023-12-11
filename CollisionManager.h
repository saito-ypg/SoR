#pragma once
#include"ActorCollider.h"
#include"AttackRange.h"
class GameActor;
//�v���C���[�w�c/�G�w�c
enum CAMPS{PLAYER,ENEMY,NUM};

//�S�ẴA�N�^�̓����蔻����Ǘ��E���肷�閼�O��ԁB�N���X�̂ق��������H
//�����蔻��̍ہA����(=y���j�͍l�����Ȃ�
namespace CollisionManager
{	

	/// <summary>
	/// �����蔻�胊�X�g�ɒǉ�
	/// </summary>
	/// <param name="newActor">�ǉ�����A�N�^</param>
	/// <param name="camp">�ǉ��������w�c</param>
	/// <returns></returns>
	void AddCamp(GameActor* newActor,CAMPS camp);

	/// <summary>
	/// �~�`�̍U���ɓ������Ă��邩���肷��
	/// </summary>
	/// <param name="camp">�U���Ґw�c</param>
	/// <param name="circle">�~�`�U���G���A</param>
	void HitTestBy(CAMPS camp,AttackRangeCircle& circle);

	/// <summary>
	/// ��`�̍U���ɓ������Ă��邩����
	/// </summary>
	/// <param name="camp">�U���Ґw�c</param>
	/// <param name="quad">��`�U���G���A</param>
	void HitTestBy(CAMPS camp, AttackRangeQuad& quad);

	/// <summary>
	/// ��`�̍U���ɓ������Ă��邩����
	/// </summary>
	/// <param name="camp">�U���Ґw�c</param>
	/// <param name="quad">��`�U���G���A</param>
	void HitTestBy(CAMPS camp, AttackRangeCirculerSector& sector);

	
	/// <summary>
	///�w�c���X�g����폜����B�|���ꂽ�ۂɌĂ� 
	/// </summary>
	/// <param name="actor">�폜�������A�N�^</param>
	/// <param name="camp">�����w�c</param>
	void RemoveCamp(GameActor*actor,CAMPS camp);



	//void Update();//������H
	void Release();//�������
}

