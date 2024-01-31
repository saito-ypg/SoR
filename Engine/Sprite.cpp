#include "Sprite.h"

Sprite::Sprite() :vertices_(nullptr), index_(nullptr), pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr), indexNum_(0), vertexNum_(0)
{
}

Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Initialize(string filename)
{
	HRESULT hr = S_OK;
	InitVertexData();

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	hr = CreateVertexBuffer();
	if (FAILED(hr))
	{
		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	InitIndexData();
	// �C���f�b�N�X�o�b�t�@�𐶐�����
	hr = CreateIndexBuffer();
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	//�R���X�^���g�o�b�t�@�쐬
	hr = CreateConstantBuffer();
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	hr = LoadTexture(filename);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

void Sprite::Draw(Transform& transform, RECT rect)
{
	using namespace Direct3D;
	Direct3D::SetShader(SHADER_2D);
	transform.Calculation();
	//��ʂɍ��킹��
		//�\������T�C�Y�ɍ��킹��
	XMMATRIX cut = XMMatrixScaling((float)rect.right, (float)rect.bottom, 1);

	XMMATRIX view = XMMatrixScaling(1.0f / scrWidth_, 1.0f / scrHeight_, 1.0f);
	XMMATRIX worldmatrix =cut*transform.matScale_ * transform.matRotate_ * view * transform.matTranslate_;

	XMMATRIX mTexTrans = XMMatrixTranslation((float)rect.left / (float)pTexture_->GetSize().x,
		(float)rect.top / (float)pTexture_->GetSize().y, 0.0f);
	XMMATRIX mTexScale = XMMatrixScaling((float)rect.right / (float)pTexture_->GetSize().x,
		(float)rect.bottom / (float)pTexture_->GetSize().y, 1.0f);
	XMMATRIX mTexel =mTexScale * mTexTrans;

	PassDataToCB(worldmatrix,mTexel);

	SetBufferToPipeline();

	Direct3D::pContext_->DrawIndexed(indexNum_, 0, 0);//!!
}

void Sprite::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	SAFE_DELETE_ARRAY(index_);
	SAFE_DELETE_ARRAY(vertices_)

}
//////initialize����//////
void Sprite::InitVertexData()
{

	vertices_ = new VERTEX[]{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },// �l�p�`�̒��_�i����j
	{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j
	{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },// �l�p�`�̒��_�i�E���j
	{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�����j		
	};
	vertexNum_ = 4;
}
HRESULT Sprite::CreateVertexBuffer()
{
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = vertexNum_ * sizeof(VERTEX);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_;
	return Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);

}
void Sprite::InitIndexData()
{
	indexNum_ = 6;
	index_ = new int[6] { 0, 2, 3, 0, 1, 2 };
}
HRESULT Sprite::CreateIndexBuffer()
{
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = indexNum_ * sizeof(int);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	return Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
}
HRESULT Sprite::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	return Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}
HRESULT Sprite::LoadTexture(string filename)
{
	pTexture_ = new Texture;
	return pTexture_->Load(filename);
}

/////////draw����/////////
void Sprite::PassDataToCB(const DirectX::XMMATRIX& worldMatrix, const XMMATRIX& texel)
{
	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(worldMatrix);
	cb.uvTrans = XMMatrixTranspose(texel);
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ
}
void Sprite::SetBufferToPipeline()
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

}
