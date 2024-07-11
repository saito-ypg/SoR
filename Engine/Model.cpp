#include "Global.h"
#include "Model.h"
//3D���f���iFBX�t�@�C���j���Ǘ�����
namespace Model
{
	//���[�h�ς݂̃��f���f�[�^�ꗗ
	std::vector < std::shared_ptr<ModelData>>	_data;

	//������
	void Initialize()
	{
		AllRelease();
	}

	//���f�������[�h
	int Load(std::string fileName)
	{
			auto pData = std::make_shared<ModelData>();


			//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
			bool isExist = false;
			for (int i = 0; i < _data.size(); i++)
			{
				//���łɊJ���Ă���ꍇ
				if (_data[i] != nullptr && _data[i]->fileName == fileName)
				{
					pData->pFbx = _data[i]->pFbx;
					isExist = true;
					break;
				}
			}

			//�V���Ƀt�@�C�����J��
			if (isExist == false)
			{
				pData->pFbx = std::make_shared<Fbx>();
				if (FAILED(pData->pFbx->Load(fileName)))
				{
					//�J���Ȃ�����
					return -1;
				}

				//�����J����
				pData->fileName = fileName;
			}


			//�g���ĂȂ��ԍ����������T��
			for (int i = 0; i < _data.size(); i++)
			{
				if (_data[i] == nullptr)
				{
					_data[i] = pData;
					return i;
				}
			}

			//�V���ɒǉ�
			_data.push_back(pData);
			return (int)_data.size() - 1;
	}



	//�`��
	void Draw(int handle)
	{
		if (handle < 0 || handle >= _data.size() || _data[handle] == nullptr)
		{
			return;
		}

		//�A�j���[�V������i�߂�
		_data[handle]->nowFrame += _data[handle]->animSpeed;

		//�Ō�܂ŃA�j���[�V����������߂�
		if (_data[handle]->nowFrame > (float)_data[handle]->endFrame)
			_data[handle]->nowFrame = (float)_data[handle]->startFrame;



		if (_data[handle]->pFbx)
		{
			_data[handle]->pFbx->Draw(_data[handle]->transform, (int)_data[handle]->nowFrame);
		}
	}



	//�S�Ẵ��f�������
	void AllRelease()
	{
		_data.clear();
	}


	//�A�j���[�V�����̃t���[�������Z�b�g
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed)
	{
		_data[handle]->SetAnimFrame(startFrame, endFrame, animSpeed);
	}


	//���݂̃A�j���[�V�����̃t���[�����擾
	int GetAnimFrame(int handle)
	{
		return (int)_data[handle]->nowFrame;
	}


	//�C�ӂ̃{�[���̈ʒu���擾
	XMFLOAT3 GetBonePosition(int handle, std::string boneName)
	{
		XMFLOAT3 pos = _data[handle]->pFbx->GetBonePosition(boneName);
		XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&pos), _data[handle]->transform.GetWorldMatrix());
		XMStoreFloat3(&pos, vec);
		return pos;
	}


	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform & transform)
	{
		if (handle < 0 || handle >= _data.size())
		{
			return;
		}

		_data[handle]->transform = transform;
	}


	//���[���h�s��̎擾
	XMMATRIX GetMatrix(int handle)
	{
		return _data[handle]->transform.GetWorldMatrix();
	}


	//���C�L���X�g�i���C���΂��ē����蔻��j
	void RayCast(int handle, RayCastData *data)
	{
			XMFLOAT3 target = Transform::Float3Add(data->start, data->dir);
			XMMATRIX matInv = XMMatrixInverse(nullptr, _data[handle]->transform.GetWorldMatrix());
			XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
			XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
			XMVECTOR vecDir = vecTarget - vecStart;

			XMStoreFloat3(&data->start, vecStart);
			XMStoreFloat3(&data->dir, vecDir);

			_data[handle]->pFbx->RayCast(data); 
	}
}