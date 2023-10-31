#pragma once
#include <DirectXMath.h>
#include"Direct3D.h"
#include "Texture.h"
#include"Transform.h"
using namespace DirectX;


class Sprite
{

	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
protected:
	UINT64 vertexNum_;
	VERTEX* vertices_;
	UINT64 indexNum_;//�C���f�b�N�X���
	int* index_;//�C���f�b�N�X���
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;   //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;//�e�N�X�`��
public:
	Sprite();
	~Sprite();
	HRESULT Initialize();
	void Draw(Transform&transform);
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
	void PassDataToCB(DirectX::XMMATRIX& wordlMatrix);
	void SetBufferToPipeline();
};

