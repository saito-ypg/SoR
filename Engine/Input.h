#pragma once
#include<DirectXMath.h>
#include <dInput.h>
using namespace DirectX;
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	HRESULT Initialize(HWND hWnd);
	HRESULT Update();
	void Release();
	//�L�[�{�[�h
	bool IsKey(int keyCode);//�L�[�������Ă����true
	bool IsKeyDown(int keyCode);//�L�[���������u�Ԃ̂�true
	bool IsKeyUp(int keyCode);//�L�[�𗣂����u�Ԃ̂�true
	//�}�E�X
	bool IsMouseButton(int buttonCode);//�}�E�X�̃{�^���������Ă����true
	bool IsMouseButtonDown(int buttonCode);//�{�^�����������u�Ԃ̂�true
	bool IsMouseButtonUp(int buttonCode);//�{�^���𗣂����u�Ԃ̂�true
	XMFLOAT3 GetMousePosition();//�}�E�X�J�[�\���̈ʒu���擾
	XMFLOAT3 GetMouseMove();//���t���[���̃}�E�X�̈ړ��ʂ��擾
	void SetMousePosition(int x, int y);
	
};
