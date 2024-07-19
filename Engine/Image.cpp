#include "Global.h"
#include "Image.h"
#include "Input.h"
namespace {
	
}
#define RETURN_IF_INVALID_HANDLE(handle) if((handle) < 0 || (handle) >= Image::_data.size()) return
//3D画像を管理する
namespace Image
{
	//ロード済みの画像データ一覧
	std::vector<std::shared_ptr<ImageData>>	_data;

	//初期化
	void Initialize()
	{
		AllRelease();
	}

	//画像をロード
	int Load(std::string fileName)
	{
		auto pData = std::make_shared<ImageData>();

		//開いたファイル一覧から同じファイル名のものが無いか探す
		bool isExist = false;
		for (int i = 0; i < _data.size(); i++)
		{
			//すでに開いている場合
			if (_data.at(i) != nullptr && _data.at(i)->fileName == fileName)
			{
				pData->pSprite = _data.at(i)->pSprite;
				isExist = true;
				break;
			}
		}

		//新たにファイルを開く
		if (isExist == false)
		{
			pData->pSprite = std::make_shared<Sprite>();
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				return -1;
			}

			//無事開けた
			pData->fileName = fileName;
		}


		//使ってない番号が無いか探す
		for (int i = 0; i < _data.size(); i++)
		{
			if (_data.at(i) == nullptr)
			{
				_data.at(i) = pData;
				return i;
			}
		}

		//新たに追加
		_data.push_back(std::move(pData));

		//画像番号割り振り
		int handle = (int)_data.size() - 1;

		//切り抜き範囲をリセット
		ResetRect(handle);

		return handle;
	}



	//描画
	void Draw(int handle)
	{
		RETURN_IF_INVALID_HANDLE(handle);
		if (_data.at(handle) == nullptr)
		{
			return;
		}
		_data.at(handle)->transform.Calculation();
		_data.at(handle)->pSprite->Draw(_data.at(handle)->transform, _data.at(handle)->rect, _data.at(handle)->alpha);
	}






	//全ての画像を解放
	void AllRelease()
	{
		_data.clear();
	}


	//切り抜き範囲の設定
	void SetRect(int handle, int x, int y, int width, int height)
	{
		RETURN_IF_INVALID_HANDLE(handle);

		_data.at(handle)->rect.left = x;
		_data.at(handle)->rect.top = y;
		_data.at(handle)->rect.right = width;
		_data.at(handle)->rect.bottom = height;
	}


	//切り抜き範囲をリセット（画像全体を表示する）
	void ResetRect(int handle)
	{
		RETURN_IF_INVALID_HANDLE(handle);

		XMFLOAT3 size = _data.at(handle)->pSprite->GetTextureSize();

		_data.at(handle)->rect.left = 0;
		_data.at(handle)->rect.top = 0;
		_data.at(handle)->rect.right = (long)size.x;
		_data.at(handle)->rect.bottom = (long)size.y;

	}

	//アルファ値設定
	void SetAlpha(int handle, int alpha)
	{
		RETURN_IF_INVALID_HANDLE(handle);
		_data.at(handle)->alpha = (float)alpha / 255.0f;
	}


	//ワールド行列を設定
	void SetTransform(int handle, Transform& transform)
	{
		RETURN_IF_INVALID_HANDLE(handle);

		_data.at(handle)->transform = transform;
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
		if ((handle) < 0 || (handle) >= Image::_data.size()) return UNSPECIFIED;
		const RECT rect_ = _data.at(handle)->rect;
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
		assert(handle < _data.size() && handle >= 0);
		XMFLOAT3 mousePos = Input::GetMousePosition();
		return isPointInside(handle, t, mousePos);
	}

	bool isPointInside(const int& handle, const Transform& ImageT, const XMFLOAT3& point)
	{
		assert(handle < _data.size() && handle >= 0);

		// 画像のスクリーン座標範囲をもとめる
		const XMFLOAT3 imgPos = toPixel(ImageT.position_);
		const XMFLOAT3 imgScale = ImageT.scale_;
		const RECT imgRect = _data.at(handle)->rect;

		float halfWidth = imgRect.right * imgScale.x / 2.0f;
		float halfHeight = imgRect.bottom * imgScale.y / 2.0f;
		float left = imgPos.x - halfWidth;
		float right = imgPos.x + halfWidth;
		float top = imgPos.y + halfHeight;
		float bottom = imgPos.y - halfHeight;

		// 座標が画像の NDC 座標範囲内にあるかを判定
		return point.x >= left && point.x <= right &&
			point.y >= bottom && point.y <= top;
	}

	//ワールド行列の取得
	XMMATRIX GetMatrix(int handle)
	{
		if (handle < 0 || handle >= _data.size())
		{
			return XMMatrixIdentity();
		}
		return _data.at(handle)->transform.GetWorldMatrix();
	}
}

