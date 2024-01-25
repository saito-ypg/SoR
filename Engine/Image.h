#pragma once
#include<string>
#include<vector>
#include"Sprite.h"
namespace Image
{
	struct ImageData
	{
		Sprite* pSprite_;//fbx
		Transform transform_;//トランスフォーム
		std::string fileName_;//ファイル名
		RECT size;
		ImageData() :pSprite_(nullptr), size() {}
	};
	int Load(std::string fileName);
	void SetTransform(int hPict, Transform transform);
	void Draw(int hPict);
	void Release(int hPict);
	void Release();//モデルを使っていないか確認
	void ResetRect(int hPict);
}

