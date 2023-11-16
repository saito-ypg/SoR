#pragma once
#include<string>
#include<vector>
#include"Sprite.h"
namespace Image
{
	struct ImageData
	{
		Sprite* pSprite_;//fbx
		Transform transform_;//�g�����X�t�H�[��
		std::string fileName_;//�t�@�C����

	};
	int Load(std::string fileName);
	void SetTransform(int hPict, Transform transform);
	void Draw(int hPict);
	void Release(int hPict);
	void Release();//���f�����g���Ă��Ȃ����m�F

}

