#include "Model.h"
#include"global.h"
namespace Model{
	
	std::vector<ModelData*> modelList_;//���f���̃|�C���^������x�N�^
}
int Model::Load(std::string fileName)
{
	//�t�@�C�����̃��f����ǂݍ��݁A�������f����������΂��̃��f���ԍ���Ԃ�
	//�������O�̃��f�����Ȃ���΁A�ǂݍ���Ńx�N�^�ɒǉ�
	/*for (int i = 0; i < modelList_.size(); i++)
	{
		if (modelList_.at(i)->fileName_ == fileName)
			return i;
	}*/

	ModelData* pData=new ModelData;
	pData->fileName_ = fileName;
	pData->pFbx_ = nullptr;

	for (auto &e : modelList_)
	{
		if (e->fileName_ == fileName)
		{
			pData->pFbx_ = e->pFbx_;
			break; 
		}
	}
	if (pData->pFbx_ == nullptr)
	{
		pData->pFbx_ = new Fbx;
		pData->pFbx_->Load(fileName);
	}
	
	modelList_.push_back(pData);
	return modelList_.size() - 1;

}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList_.at(hModel)->transform_ = transform;
}

void Model::Draw(int hModel)
{
	modelList_.at(hModel)->pFbx_->Draw(modelList_.at(hModel)->transform_);
}

void Model::Release(int hModel)
{
	
}

void Model::Release()
{
	bool isReffered = false;
	for (int i = 0; i < modelList_.size(); i++)
	{
		for (int j = i + 1; j < modelList_.size(); j++)
		{
			if (modelList_.at(i)->pFbx_ == modelList_.at(j)->pFbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (!isReffered)
		{
			SAFE_DELETE(modelList_.at(i)->pFbx_);
		}
		SAFE_DELETE(modelList_.at(i));
	}

	modelList_.clear();
}

void Model::RayCast(int hModel, RayCastData& raydata)
{
	modelList_.at(hModel)->transform_.Calculation();
	//RayCast�O��raycastData�̊e�������[���h��Ԃ��烂�f����Ԃɕϊ�����
	XMMATRIX invWorld=XMMatrixInverse(nullptr,modelList_.at(hModel)->transform_.GetWorldMatrix());
	XMVECTOR vPass{ raydata.start.x + raydata.dir.x, raydata.start.y + raydata.dir.y, raydata.start.z + raydata.dir.z , raydata.start.w + raydata.dir.w };
	XMVECTOR vStart = XMVector3TransformCoord(XMLoadFloat4(&raydata.start), invWorld);
	XMStoreFloat4(&raydata.start, vStart);
	vPass = XMVector3TransformCoord(vPass, invWorld);
	vPass = vPass - vStart;

	XMStoreFloat4(&raydata.dir, vPass);

	//XMStoreFloat4(&raydata.dir, XMVector4Normalize(XMLoadFloat4(&raydata.dir)));//�P�ʃx�N�g���ɂ��Ȃ��ƃG���[���o��?
	modelList_.at(hModel)->pFbx_->RayCast(raydata);
}
