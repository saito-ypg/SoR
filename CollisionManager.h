#pragma once
#include<vector>
#include"ActorCollider.h"
#include<map>
class GameActor;
namespace CollisionManager
{
	std::map<GameActor* ,ActorCollider*> enemiesCampCollision;
	std::map<GameActor* ,ActorCollider*> playersCampCollision;
	
	//�v���C���[�w�c�̓����蔻�胊�X�g�ɒǉ�����B
	[[nodiscard]] ActorCollider* AddPlayerCamp(GameActor* newActor);

	//�G�w�c�̓����蔻�胊�X�g�ɒǉ�����B
	[[nodiscard]] ActorCollider* AddEnemyCamp(GameActor* newActor);
	//�v���C���[�̍U���ɓ������Ă���G���A�Ԃ�or�ʃ����o�ɓ���Ƃ��B�e�`��ŃI�[�o�[���[�h
	auto HitTestByPlayer(/*�U���������蔻��N���X*/);
	//�G�̍U���ɓ������Ă���v���C���[��������...
	auto HitTestByEnemy();

	void RemoveEnemyCamp(GameActor*);
	void RemovePlayerCamp(GameActor*);

}

