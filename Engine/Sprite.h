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
		XMMATRIX	uvTrans;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
protected:
	UINT vertexNum_;
	VERTEX* vertices_;
	UINT indexNum_;//�C���f�b�N�X���
	int* index_;//�C���f�b�N�X���
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;   //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;//�e�N�X�`��
public:
	Sprite();
	~Sprite();
	HRESULT Initialize(string filename);
	void Draw(Transform&transform, RECT rect);
	void Release();
//�摜�T�C�Y�̎擾
	//�ߒl�F�摜�T�C�Y
	XMFLOAT3 GetTextureSize() { return pTexture_->GetSize(); }
private:
	//initialize���̊֐�
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture(string filename);


	//Draw�֐�����Ă΂��֐�
	void PassDataToCB(const DirectX::XMMATRIX& wordlMatrix,const XMMATRIX&texel);
	void SetBufferToPipeline();


	

};

