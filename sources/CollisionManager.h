#pragma once
#include"ActorCollider.h"
#include"AttackRange.h"

//�v���C���[�w�c/�G�w�c
enum CAMPS{PLAYER,ENEMY,NUM};
class GameActor;
struct DamageData;
struct actorAddr {
	GameActor* pActor;//�L����
	ActorCollider* pCollider;//�L�����̓����蔻��
	actorAddr() :pActor(nullptr), pCollider(nullptr) {}
	actorAddr(GameActor* pA, ActorCollider* pC) :pActor(pA), pCollider(pC) {}
};
//�S�ẴA�N�^�̓����蔻����Ǘ��E���肷�閼�O��ԁB
//�����蔻��̍ہA����(=y���j�͍l�����Ȃ�
namespace CollisionManager
{
	/// <summary>
	/// �V�[���̃A�b�v�f�[�g�ł�����Ă�
	/// �����蔻�肪��������Ԕ��肵������Ƃ�
	/// </summary>
	void Update(const float&dt);
	
	/// <summary>
	/// �����蔻�胊�X�g�ɒǉ�
	/// </summary>
	/// <param name="newActor">�ǉ�����A�N�^</param>
	/// <param name="camp">�ǉ��������w�c</param>
	/// <returns></returns>
	void AddCamp(GameActor* newActor,CAMPS camp);


	void RegisterHitRange(CAMPS camp, AttackRangeCircle c, DamageData dmg, std::function<void(float)> func);
	void RegisterHitRange(CAMPS camp, AttackRangeQuad q, DamageData dmg, std::function<void(float)>func);
	void RegisterHitRange(CAMPS camp, AttackRangeCirculerSector s, DamageData dmg, std::function<void(float)>func);
	/// <summary>
	///�w�c���X�g����폜����B�|���ꂽ�ۂɌĂ� 
	/// </summary>
	/// <param name="actor">�폜�������A�N�^</param>
	/// <param name="camp">�����w�c</param>
	void RemoveCamp(GameActor*actor,CAMPS camp);

	void Release();//�������
}

