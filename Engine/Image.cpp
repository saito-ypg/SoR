#include "Global.h"
#include "Image.h"
namespace {
	
}
#define RET_IF_NON_EXIST(handle) if((handle) < 0 || (handle) >= Image::_datas.size()) return
//3D画像を管理する
namespace Image
{
	//ロード済みの画像データ一覧
	std::vector<ImageData*>	_datas;

	//初期化
	void Initialize()
	{
		AllRelease();
	}

	//画像をロード
	int Load(std::string fileName)
	{
		ImageData* pData = new ImageData;

		//開いたファイル一覧から同じファイル名のものが無いか探す
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->pSprite = _datas[i]->pSprite;
				isExist = true;
				break;
			}
		}

		//新たにファイルを開く
		if (isExist == false)
		{
			pData->pSprite = new Sprite;
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				//開けなかった
				SAFE_DELETE(pData->pSprite);
				SAFE_DELETE(pData);
				return -1;
			}

			//無事開けた
			pData->fileName = fileName;
		}


		//使ってない番号が無いか探す
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//新たに追加
		_datas.push_back(pData);

		//画像番号割り振り
		int handle = (int)_datas.size() - 1;

		//切り抜き範囲をリセット
		ResetRect(handle);

		return handle;
	}



	//描画
	void Draw(int handle)
	{
		RET_IF_NON_EXIST(handle);
		if (_datas[handle] == nullptr)
		{
			return;
		}
		_datas[handle]->transform.Calclation();
		_datas[handle]->pSprite->Draw(_datas[handle]->transform, _datas[handle]->rect, _datas[handle]->alpha);
	}



	//任意の画像を開放
	void Release(int handle)
	{

		//同じモデルを他でも使っていないか
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && i != handle && _datas[i]->pSprite == _datas[handle]->pSprite)
			{
				isExist = true;
				break;
			}
		}

		//使ってなければモデル解放
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->pSprite);
		}

		SAFE_DELETE(_datas[handle]);
	}



	//全ての画像を解放
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//切り抜き範囲の設定
	void SetRect(int handle, int x, int y, int width, int height)
	{
		RET_IF_NON_EXIST(handle);

		_datas[handle]->rect.left = x;
		_datas[handle]->rect.top = y;
		_datas[handle]->rect.right = width;
		_datas[handle]->rect.bottom = height;
	}


	//切り抜き範囲をリセット（画像全体を表示する）
	void ResetRect(int handle)
	{
		RET_IF_NON_EXIST(handle);

		XMFLOAT3 size = _datas[handle]->pSprite->GetTextureSize();

		_datas[handle]->rect.left = 0;
		_datas[handle]->rect.top = 0;
		_datas[handle]->rect.right = (long)size.x;
		_datas[handle]->rect.bottom = (long)size.y;

	}

	//アルファ値設定
	void SetAlpha(int handle, int alpha)
	{
		RET_IF_NON_EXIST(handle);
		_datas[handle]->alpha = (float)alpha / 255.0f;
	}


	//ワールド行列を設定
	void SetTransform(int handle, Transform& transform)
	{
		RET_IF_NON_EXIST(handle);

		_datas[handle]->transform = transform;
	}

	XMFLOAT3 toPixel(XMFLOAT3 pos)
	{
		return XMFLOAT3((pos.x+1.0f)/2*Direct3D::screenWidth_, (pos.y + 1.0f) / -2 * Direct3D::screenHeight_,0);
	}

	XMFLOAT3 toPos(XMFLOAT3 pixel)
	{
		return XMFLOAT3(pixel.x/Direct3D::screenWidth_*2-1,pixel.y/Direct3D::screenHeight_*-2+1,0);
	}

	float AlignImage(int handle, PLACEMENT placement)
	{	
		switch (placement)
		{
		case LEFT:
		case RIGHT:
			return AlignImage(handle, placement, Direct3D::screenWidth_);
		case UP:
		case DOWN:
			return AlignImage(handle, placement, Direct3D::screenHeight_);
		default:
			return NAN;
		}
	}	


	float AlignImage(int handle, PLACEMENT placement, float specifiedPos)
	{
		if ((handle) < 0 || (handle) >= Image::_datas.size()) return NAN;
		RECT rect_ = _datas.at(handle)->rect;
		switch (placement)
		{
		case LEFT:
			return toPos(XMFLOAT3((rect_.right / 2), 0, 0)).x;
		case RIGHT:
			return toPos(XMFLOAT3(specifiedPos - (rect_.right / 2), 0, 0)).x;
		case UP:
			return toPos(XMFLOAT3(0, rect_.bottom / 2, 0)).y;
		case DOWN:
			return toPos(XMFLOAT3(0, specifiedPos - (rect_.bottom / 2), 0)).y;
		}
		return 0;
	}

	//ワールド行列の取得
	XMMATRIX GetMatrix(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return XMMatrixIdentity();
		}
		return _datas[handle]->transform.GetWorldMatrix();
	}
}

