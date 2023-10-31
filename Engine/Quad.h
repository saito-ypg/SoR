#pragma once
#include <DirectXMath.h>
#include"Direct3D.h"
#include "Texture.h"
#include"Transform.h"
using namespace DirectX;

//�R���X�^���g�o�b�t�@�[



class Quad
{
protected:
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	UINT64 vertexNum_;
	VERTEX* vertices_;
	UINT64 indexNum_;//�C���f�b�N�X���
	int* index_;//�C���f�b�N�X���
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;   //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;//�e�N�X�`��
public:
	Quad();
	virtual ~Quad();
	HRESULT Initialize();
	void Draw(Transform& transform);
	void Release();

private:
	//initialize���̊֐�
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();


	//Draw�֐�����Ă΂��֐�
	void PassDataToCB(Transform transform);
	void SetBufferToPipeline();
};

