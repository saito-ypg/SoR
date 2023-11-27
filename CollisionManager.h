#pragma once
#include<vector>
#include"ActorCollider.h"
#include<map>
class GameActor;
//�v���C���[�w�c/�G�w�c
enum CAMPS{PLAYER,ENEMY};

//�S�ẴA�N�^�̓����蔻����Ǘ��E���肷�閼�O��ԁB�N���X�̂ق��������H
namespace CollisionManager
{	
	//�e�w�c�̓����蔻��
	std::vector<std::map<GameActor*, ActorCollider*>>CollisionList;

	/// <summary>
	/// �����蔻�胊�X�g�ɒǉ�
	/// </summary>
	/// <param name="newActor">�ǉ�����A�N�^</param>
	/// <param name="camp">�ǉ��������w�c</param>
	/// <returns></returns>
	[[nodiscard]] ActorCollider* AddCamp(GameActor* newActor,CAMPS camp);
	//�v���C���[�̍U���ɓ������Ă���G���A�Ԃ�or�ʃ����o�ɓ���Ƃ��B�e�`��ŃI�[�o�[���[�h
	auto HitTestBy(/*�U���������蔻��N���X*/);
	
	/// <summary>
	///�w�c���X�g����폜����B�|���ꂽ�ۂɌĂ� 
	/// </summary>
	/// <param name="actor">�폜�������A�N�^</param>
	/// <param name="camp">�����w�c</param>
	void RemoveCamp(GameActor*actor,CAMPS camp);

	/// <summary>
	/// �U�����󂯂����Ƃ�ʒm���A�eactor��TakeAttacked���Ă�
	/// </summary>
	void NotifyReceivedAttack();

	//void Update();//������H
	void Release();//�������
}

