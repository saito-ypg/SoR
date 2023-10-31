#pragma once
#include<d3d11.h>
#include <cassert>
//�����J
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p!=nullptr){delete[] p;p=nullptr;}
enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX
};
namespace Direct3D
{
	extern ID3D11Device* pDevice_;
	extern ID3D11DeviceContext* pContext_;
	extern int scrWidth_, scrHeight_;//���N���X�p�ێ�
	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type);
	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

};