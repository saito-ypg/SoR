#pragma once
#include"Engine/Transform.h"


class ActorCollider //�L�������̓����蔻��̑傫��
{	
private:
	
protected:
	Transform transform_;//�����I�u�W�F�N�g�̒l�����̂܂܎����Ƃ��B�X�V�́c�ǂ����悤
public:
	Transform offset_;//�����I�u�W�F�N�g����̃I�t�Z�b�g�A�Ȃ����ALL0
	ActorCollider();
	~ActorCollider();

};

