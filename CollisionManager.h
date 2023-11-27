#pragma once
#include<vector>
#include"ActorCollider.h"
#include<map>
class GameActor;
//�v���C���[�w�c/�G�w�c
enum CAMPS{PLAYER,ENEMY};

//�S�ẴA�N�^�̓����蔻����Ǘ��E���肷�閼�O��ԁB�N���X�̂ق��������H
namespace CollisionManager
{//
	/*std::map<GameActor* ,ActorCollider*> enemiesCampCollision;
	std::map<GameActor* ,ActorCollider*> playersCampCollision;*/

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
	//�G�̍U���ɓ������Ă���v���C���[��������...
	auto HitTestByEnemy();

	//�G�w�c�̃��X�g����폜����B�|���ꂽ�Ƃ��ɌĂ�
	void RemoveEnemyCamp(GameActor*actor);

	//�����w�c�̃��X�g����폜����B�|���ꂽ�Ƃ��ɌĂ�
	void RemovePlayerCamp(GameActor*actor);

	/// <summary>
	/// �U�����󂯂����Ƃ�ʒm���A�eactor��TakeAttacked���Ă�
	/// </summary>
	void NotifyReceivedAttack();

	//void Update();//������H
	void Release();//�������
}

