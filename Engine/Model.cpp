#include "Global.h"
#include "Model.h"
//3Dモデル（FBXファイル）を管理する
namespace Model
{
	//ロード済みのモデルデータ一覧
	std::vector < std::shared_ptr<ModelData>>	_data;

	//初期化
	void Initialize()
	{
		AllRelease();
	}

	//モデルをロード
	int Load(std::string fileName)
	{
			auto pData = std::make_shared<ModelData>();


			//開いたファイル一覧から同じファイル名のものが無いか探す
			bool isExist = false;
			for (int i = 0; i < _data.size(); i++)
			{
				//すでに開いている場合
				if (_data[i] != nullptr && _data[i]->fileName == fileName)
				{
					pData->pFbx = _data[i]->pFbx;
					isExist = true;
					break;
				}
			}

			//新たにファイルを開く
			if (isExist == false)
			{
				pData->pFbx = std::make_shared<Fbx>();
				if (FAILED(pData->pFbx->Load(fileName)))
				{
					//開けなかった
					return -1;
				}

				//無事開けた
				pData->fileName = fileName;
			}


			//使ってない番号が無いか探す
			for (int i = 0; i < _data.size(); i++)
			{
				if (_data[i] == nullptr)
				{
					_data[i] = pData;
					return i;
				}
			}

			//新たに追加
			_data.push_back(pData);
			return (int)_data.size() - 1;
	}



	//描画
	void Draw(int handle)
	{
		if (handle < 0 || handle >= _data.size() || _data[handle] == nullptr)
		{
			return;
		}

		//アニメーションを進める
		_data[handle]->nowFrame += _data[handle]->animSpeed;

		//最後までアニメーションしたら戻す
		if (_data[handle]->nowFrame > (float)_data[handle]->endFrame)
			_data[handle]->nowFrame = (float)_data[handle]->startFrame;



		if (_data[handle]->pFbx)
		{
			_data[handle]->pFbx->Draw(_data[handle]->transform, (int)_data[handle]->nowFrame);
		}
	}



	//全てのモデルを解放
	void AllRelease()
	{
		_data.clear();
	}


	//アニメーションのフレーム数をセット
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed)
	{
		_data[handle]->SetAnimFrame(startFrame, endFrame, animSpeed);
	}


	//現在のアニメーションのフレームを取得
	int GetAnimFrame(int handle)
	{
		return (int)_data[handle]->nowFrame;
	}


	//任意のボーンの位置を取得
	XMFLOAT3 GetBonePosition(int handle, std::string boneName)
	{
		XMFLOAT3 pos = _data[handle]->pFbx->GetBonePosition(boneName);
		XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&pos), _data[handle]->transform.GetWorldMatrix());
		XMStoreFloat3(&pos, vec);
		return pos;
	}


	//ワールド行列を設定
	void SetTransform(int handle, Transform & transform)
	{
		if (handle < 0 || handle >= _data.size())
		{
			return;
		}

		_data[handle]->transform = transform;
	}


	//ワールド行列の取得
	XMMATRIX GetMatrix(int handle)
	{
		return _data[handle]->transform.GetWorldMatrix();
	}


	//レイキャスト（レイを飛ばして当たり判定）
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