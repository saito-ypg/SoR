#include "Texture.h"
#include"Direct3D.h"
#include<DirectXTex.h>
#include"global.h"
#pragma comment(lib,"DirectXTex.lib")

Texture::Texture() :pSampleLinear_(nullptr), pTextureSRV_(nullptr), size_(0, 0, 0)
{
}

Texture::~Texture()
{
	Release();
}

HRESULT Texture::Load(std::string fileName)
{
	using namespace DirectX;
	//�摜�ǂݍ���
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());
	DirectX::TexMetadata metadata;
	ScratchImage image;
	HRESULT hr = S_OK;
	hr = LoadFromWICFile(wtext, WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "�摜�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	size_ = XMFLOAT3{ (float)metadata.width ,(float)metadata.height,0 };

	//�T���v���[�̍쐬
	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = Direct3D::pDevice_->CreateSamplerState(&SamDesc, &pSampleLinear_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�摜�T���v���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	//�V�F�[�_�[���\�[�X�r���[�̍쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = CreateShaderResourceView(Direct3D::pDevice_, image.GetImages(), image.GetImageCount(), metadata, &pTextureSRV_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;

}

void Texture::Release()
{
	SAFE_RELEASE(pSampleLinear_);
	SAFE_RELEASE(pTextureSRV_);
}