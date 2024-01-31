#pragma once
#include <DirectXMath.h>
#include"Direct3D.h"
#include "Texture.h"
#include"Transform.h"
using namespace DirectX;


class Sprite
{

	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
		XMMATRIX	uvTrans;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
protected:
	UINT vertexNum_;
	VERTEX* vertices_;
	UINT indexNum_;//インデックス情報
	int* index_;//インデックス情報
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;   //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;//テクスチャ
public:
	Sprite();
	~Sprite();
	HRESULT Initialize(string filename);
	void Draw(Transform&transform, RECT rect);
	void Release();
//画像サイズの取得
	//戻値：画像サイズ
	XMFLOAT3 GetTextureSize() { return pTexture_->GetSize(); }
private:
	//initialize内の関数
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture(string filename);


	//Draw関数から呼ばれる関数
	void PassDataToCB(const DirectX::XMMATRIX& wordlMatrix,const XMMATRIX&texel);
	void SetBufferToPipeline();


	

};

