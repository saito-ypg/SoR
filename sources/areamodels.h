#pragma once

//汎用、範囲表示するモデル
namespace AreaModels
{
	enum AREATYPE {
		CIRCLE, QUAD, SECTOR, NONE
	};
	void Initialize();
	const int area(AREATYPE handle);//ハンドルを返す。
};

