#include "Global.h"
#include "Image.h"
namespace {
	
}
#define RET_IF_NON_EXIST(handle) if((handle) < 0 || (handle) >= Image::_datas.size()) return
//3D�摜���Ǘ�����
namespace Image
{
	//���[�h�ς݂̉摜�f�[�^�ꗗ
	std::vector<ImageData*>	_datas;

	//������
	void Initialize()
	{
		AllRelease();
	}

	//�摜�����[�h
	int Load(std::string fileName)
	{
		ImageData* pData = new ImageData;

		//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas.at(i) != nullptr && _datas.at(i)->fileName == fileName)
			{
				pData->pSprite = _datas.at(i)->pSprite;
				isExist = true;
				break;
			}
		}

		//�V���Ƀt�@�C�����J��
		if (isExist == false)
		{
			pData->pSprite = new Sprite;
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				//�J���Ȃ�����
				SAFE_DELETE(pData->pSprite);
				SAFE_DELETE(pData);
				return -1;
			}

			//�����J����
			pData->fileName = fileName;
		}


		//�g���ĂȂ��ԍ����������T��
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas.at(i) == nullptr)
			{
				_datas.at(i) = pData;
				return i;
			}
		}

		//�V���ɒǉ�
		_datas.push_back(pData);

		//�摜�ԍ�����U��
		int handle = (int)_datas.size() - 1;

		//�؂蔲���͈͂����Z�b�g
		ResetRect(handle);

		return handle;
	}



	//�`��
	void Draw(int handle)
	{
		RET_IF_NON_EXIST(handle);
		if (_datas.at(handle) == nullptr)
		{
			return;
		}
		_datas.at(handle)->transform.Calclation();
		_datas.at(handle)->pSprite->Draw(_datas.at(handle)->transform, _datas.at(handle)->rect, _datas.at(handle)->alpha);
	}



	//�C�ӂ̉摜���J��
	void Release(int handle)
	{

		//�������f���𑼂ł��g���Ă��Ȃ���
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas.at(i) != nullptr && i != handle && _datas.at(i)->pSprite == _datas.at(handle)->pSprite)
			{
				isExist = true;
				break;
			}
		}

		//�g���ĂȂ���΃��f�����
		if (isExist == false)
		{
			SAFE_DELETE(_datas.at(handle)->pSprite);
		}

		SAFE_DELETE(_datas.at(handle));
	}



	//�S�Ẳ摜�����
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//�؂蔲���͈͂̐ݒ�
	void SetRect(int handle, int x, int y, int width, int height)
	{
		RET_IF_NON_EXIST(handle);

		_datas.at(handle)->rect.left = x;
		_datas.at(handle)->rect.top = y;
		_datas.at(handle)->rect.right = width;
		_datas.at(handle)->rect.bottom = height;
	}


	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
	void ResetRect(int handle)
	{
		RET_IF_NON_EXIST(handle);

		XMFLOAT3 size = _datas.at(handle)->pSprite->GetTextureSize();

		_datas.at(handle)->rect.left = 0;
		_datas.at(handle)->rect.top = 0;
		_datas.at(handle)->rect.right = (long)size.x;
		_datas.at(handle)->rect.bottom = (long)size.y;

	}

	//�A���t�@�l�ݒ�
	void SetAlpha(int handle, int alpha)
	{
		RET_IF_NON_EXIST(handle);
		_datas.at(handle)->alpha = (float)alpha / 255.0f;
	}


	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform& transform)
	{
		RET_IF_NON_EXIST(handle);

		_datas.at(handle)->transform = transform;
	}

	XMFLOAT3 toPixel(XMFLOAT3 pos)
	{
		return XMFLOAT3((pos.x+1.0f)/2*Direct3D::screenWidth_, (pos.y + 1.0f) / -2 * Direct3D::screenHeight_,0);
	}

	float toPixel(float pos, AXIS axis)
	{
		switch (axis) {
		case X:return((pos+1.0f)/2*Direct3D::screenWidth_);
		case Y:return((pos+1.0f)/-2*Direct3D::screenHeight_);
		default:assert(false);
		}
	}

	XMFLOAT3 toPos(XMFLOAT3 pixel)
	{
		return XMFLOAT3(pixel.x/Direct3D::screenWidth_*2-1,pixel.y/Direct3D::screenHeight_*-2+1,0);
	}

	float toPos(float pixel, AXIS axis)
	{
		switch (axis) {
		case X:return((pos + 1.0f) / 2 * Direct3D::screenWidth_);
		case Y:return((pos + 1.0f) / -2 * Direct3D::screenHeight_);
		default:assert(false);
		}
	}

	float AlignImage(int handle, PLACEMENT placement)
	{	
		switch (placement)
		{
		case LEFT:
		case RIGHT:
			return AlignImage(handle, placement, (float)Direct3D::screenWidth_);
		case UP:
		case DOWN:
			return AlignImage(handle, placement, (float)Direct3D::screenHeight_);
		default:
			return -9999;
		}
	}	

	float AlignImage(int handle, PLACEMENT placement, float specifiedPos, float scale=1.0f)
	{
		if ((handle) < 0 || (handle) >= Image::_datas.size()) return NAN;
		const RECT rect_ = _datas.at(handle)->rect;
		const float halfWidth = rect_.right / 2.0f*scale;
		const float halfHeight = rect_.bottom / 2.0f*scale;
		float retPos;
		switch (placement)
		{
		case LEFT:
			retPos = (XMFLOAT3(halfWidth, 0, 0)).x;	break;
		case RIGHT:
			retPos = (XMFLOAT3(specifiedPos - (halfWidth), 0, 0)).x; break;
		case UP:
			retPos = (XMFLOAT3(0, halfHeight, 0)).y; break;
		case DOWN:
			retPos = (XMFLOAT3(0, specifiedPos - (halfHeight), 0)).y; break;
		default:
			return NAN;
		}
		return retPos;
	}

	//���[���h�s��̎擾
	XMMATRIX GetMatrix(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return XMMatrixIdentity();
		}
		return _datas.at(handle)->transform.GetWorldMatrix();
	}
}

