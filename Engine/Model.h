#pragma once
#include<string>
#include"Fbx.h"
namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_;//fbx
		Transform transform_;//�g�����X�t�H�[��
		std::string fileName_;//�t�@�C����
		ModelData():pFbx_(nullptr){}
	};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release(int hModel);
	void ReleaseAll();//���f�����g���Ă��Ȃ����m�F
	void RayCast(int hModel, RayCastData& raydata);//���f���ԍ����w�肵�A����FBX�Ƀ��C�L���X�g�������Ȃ�
	
}

