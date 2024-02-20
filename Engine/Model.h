#pragma once
#include<string>
#include"Fbx.h"
namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_;//fbx
		Transform transform_;//トランスフォーム
		std::string fileName_;//ファイル名
		ModelData():pFbx_(nullptr){}
	};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release(int hModel);
	void ReleaseAll();//モデルを使っていないか確認
	void RayCast(int hModel, RayCastData& raydata);//モデル番号を指定し、そのFBXにレイキャストをおこなう
	
}

