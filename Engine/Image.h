#pragma once
#include<string>
#include<vector>
#include"Sprite.h"
namespace Model
{
	struct ModelData
	{
		Sprite* pSprite_;//fbx
		Transform transform_;//�g�����X�t�H�[��
		std::string fileName_;//�t�@�C����

	};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release(int hModel);
	void Release();//���f�����g���Ă��Ȃ����m�F

}

