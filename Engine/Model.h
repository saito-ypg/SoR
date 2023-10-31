#pragma once
#include<string>
#include<vector>
#include"Fbx.h"
namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_;//fbx
		Transform transform_;//�g�����X�t�H�[��
		std::string fileName_;//�t�@�C����

	};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release(int hModel);
	void Release();//���f�����g���Ă��Ȃ����m�F
	void RayCast(int hModel, RayCastData& raydata);//���f���ԍ����w�肵�A����FBX�Ƀ��C�L���X�g�������Ȃ�
	
}

