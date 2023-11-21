#pragma once
#include<vector>
#include"ActorCollider.h"
#include<map>
class GameActor;
namespace CollisionManager
{
	std::map<ActorCollider*, GameActor*> enemiesCampCollision;
	std::map<ActorCollider*, GameActor*> playersCampCollision;
	
	//�v���C���[�w�c�̓����蔻�胊�X�g�ɒǉ�����B
	[[nodiscard]] ActorCollider* AddPlayerCollision(GameActor* newActor);
	//�G�w�c�̓����蔻�胊�X�g�ɒǉ�����B
	[[nodiscard]] ActorCollider* AddEnemyCollision(GameActor* newActor);
	auto HitTestPlayer(/*�U���������蔻��N���X*/);//���X�g�S�����ē������Ă���̂�Ԃ�or�ʃ����o�ɓ���Ƃ��B�e�`��ŃI�[�o�[���[�h
	auto HitTestEnemy();

	void RemoveEnemyCamp(GameActor*);
	void RemovePlayerCamp(GameActor*);

}

