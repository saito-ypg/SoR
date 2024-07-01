#include "Global.h"
#include "Image.h"
#include "Input.h"
namespace {
	
}
#define RETURN_IF_INVALID_HANDLE(handle) if((handle) < 0 || (handle) >= Image::_datas.size()) return
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
		RETURN_IF_INVALID_HANDLE(handle);
		if (_datas.at(handle) == nullptr)
		{
			return;
		}
		_datas.at(handle)->transform.Calculation();
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
		RETURN_IF_INVALID_HANDLE(handle);

		_datas.at(handle)->rect.left = x;
		_datas.at(handle)->rect.top = y;
		_datas.at(handle)->rect.right = width;
		_datas.at(handle)->rect.bottom = height;
	}


	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
	void ResetRect(int handle)
	{
		RETURN_IF_INVALID_HANDLE(handle);

		XMFLOAT3 size = _datas.at(handle)->pSprite->GetTextureSize();

		_datas.at(handle)->rect.left = 0;
		_datas.at(handle)->rect.top = 0;
		_datas.at(handle)->rect.right = (long)size.x;
		_datas.at(handle)->rect.bottom = (long)size.y;

	}

	//�A���t�@�l�ݒ�
	void SetAlpha(int handle, int alpha)
	{
		RETURN_IF_INVALID_HANDLE(handle);
		_datas.at(handle)->alpha = (float)alpha / 255.0f;
	}


	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform& transform)
	{
		RETURN_IF_INVALID_HANDLE(handle);

		_datas.at(handle)->transform = transform;
	}

	XMFLOAT3 toPixel(const XMFLOAT3& pos)
	{
		return XMFLOAT3((pos.x+1.0f)*0.5f*Direct3D::screenWidth_,
						(1.0f-pos.y) *0.5f*Direct3D::screenHeight_,
						0.0f);
	}

	float toPixel(const float& pos, const AXIS& axis)
	{
		switch (axis) {
		case X:return((pos+1.0f)*0.5f*Direct3D::screenWidth_);
		case Y:return((1.0f-pos) * 0.5f *Direct3D::screenHeight_);
		default:assert(false);
			return 0.0f;
		}
	}

	XMFLOAT3 toPos(XMFLOAT3 pixel)
	{
		return XMFLOAT3(pixel.x/Direct3D::screenWidth_*2-1,pixel.y/Direct3D::screenHeight_*-2+1,0);
	}

	float toPos(float pixel, AXIS axis)
	{
		switch (axis) {
		case X:return(pixel / Direct3D::screenWidth_ * 2 - 1);
		case Y:return(pixel / Direct3D::screenHeight_ * -2 + 1);
		default:assert(false); return UNSPECIFIED;
		}
	}


	float AlignImage(const int& handle, const PLACEMENT& placement, float specifiedPos, float scale)
	{
		if ((handle) < 0 || (handle) >= Image::_datas.size()) return UNSPECIFIED;
		const RECT rect_ = _datas.at(handle)->rect;
		const float halfWidth = (rect_.right -rect_.left)*0.5f*scale;
		const float halfHeight = (rect_.bottom-rect_.top )*0.5f*scale;
		float retPos;
		bool nan = isnan<float>(specifiedPos);
		switch (placement)
		{
		case LEFT:
			if (nan)
				specifiedPos = 0.0f;
			retPos = halfWidth+specifiedPos;	break;
		case RIGHT:
			if (nan)
				specifiedPos = static_cast<float>(Direct3D::screenWidth_);
			retPos = specifiedPos - halfWidth; break;
		case UP:
			if (nan)
				specifiedPos = 0.0f;
			retPos = halfHeight+specifiedPos; break;
		case DOWN:
			if (nan)
				specifiedPos = static_cast<float>(Direct3D::screenHeight_);
			retPos = specifiedPos - halfHeight; break;
		default:
			return NAN;
		}
		return retPos;
	}

	bool isMouseOver(const int& handle, const Transform &t)
	{
		assert(handle < _datas.size() && handle >= 0);
		XMFLOAT3 mousePos = Input::GetMousePosition();
		return isPointInside(handle, t, mousePos);
	}

	bool isPointInside(const int& handle, const Transform& ImageT, const XMFLOAT3& point)
	{
		assert(handle < _datas.size() && handle >= 0);

		// �摜�̃X�N���[�����W�͈͂����Ƃ߂�
		const XMFLOAT3 imgPos = toPixel(ImageT.position_);
		const XMFLOAT3 imgScale = ImageT.scale_;
		const RECT imgRect = _datas.at(handle)->rect;

		float halfWidth = imgRect.right * imgScale.x / 2.0f;
		float halfHeight = imgRect.bottom * imgScale.y / 2.0f;
		float left = imgPos.x - halfWidth;
		float right = imgPos.x + halfWidth;
		float top = imgPos.y + halfHeight;
		float bottom = imgPos.y - halfHeight;

		// ���W���摜�� NDC ���W�͈͓��ɂ��邩�𔻒�
		return point.x >= left && point.x <= right &&
			point.y >= bottom && point.y <= top;
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

