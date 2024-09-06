#include "areamodels.h"
#include"Engine/Model.h"
namespace AreaModels
{
	int handles[AreaModels::AREATYPE::NONE] = { -1,-1,-1 };
	void Initialize()
	{
		handles[CIRCLE] = Model::Load("Area\\CircleArea.fbx");
		handles[QUAD] = Model::Load("Area\\QuadArea.fbx");
		handles[SECTOR] = Model::Load("Area\\SectorArea.fbx");
		assert(handles[CIRCLE] >= 0);
		assert(handles[QUAD] >= 0);
		assert(handles[SECTOR] >= 0);
	}
	const int area(AREATYPE handle)
	{
		return handles[handle];
	}
}