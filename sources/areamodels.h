#pragma once

//�ėp�A�͈͕\�����郂�f��
namespace AreaModels
{
	enum AREATYPE {
		CIRCLE, QUAD, SECTOR, NONE
	};
	void Initialize();
	const int area(AREATYPE handle);//�n���h����Ԃ��B
};

