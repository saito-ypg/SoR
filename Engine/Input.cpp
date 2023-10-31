#include "Input.h"
#include<DirectXMath.h>
#include<string>
using std::string;
namespace Input
{
	LPDIRECTINPUT8   pDInput_ = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice_ = nullptr;
	LPDIRECTINPUTDEVICE8 pMouseDevice_ = nullptr;
	BYTE keyState_[256] = { 0 };
	BYTE prevKeyState_[256] = { 0 }; //�O�t���[���ł̊e�L�[�̏��
	DIMOUSESTATE mouseState_;
	DIMOUSESTATE prevMouseState_;
	XMFLOAT3 mousePosition_;

	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr=S_OK;
		hr=DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);//Input�{�̍쐬
		if (FAILED(hr)) return hr;
		hr=pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);//�L�[�{�[�h�Ƃ��ăf�o�C�X���쐬
		if (FAILED(hr)) return hr;
		hr=pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) return hr;
		hr=pKeyDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) return hr;
		
		//�}�E�X�o�^
		hr = pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		if (FAILED(hr)) return hr;
		hr = pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		if (FAILED(hr)) return hr;
		hr = pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) return hr;

		return S_OK;
	}

	HRESULT Update()
	{
		//�L�[�{�[�h
		memcpy(prevKeyState_,keyState_,sizeof(keyState_[0]) * 256);
		HRESULT hr=pKeyDevice_->Acquire();
		if (FAILED(hr)) return hr;
		hr=pKeyDevice_->GetDeviceState(sizeof(keyState_), &keyState_);
		if (FAILED(hr)) return hr;

		//�}�E�X	
		hr = pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		if (FAILED(hr)) return hr;
		hr = pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
		if (FAILED(hr)) return hr;
		return S_OK;
	}

	bool IsKey(int keyCode)
	{
		if (keyState_[keyCode]&0x80)	
		{
			return true;
		}
		return false;
	}
	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if ((keyState_[keyCode] & 0x80)&& !(prevKeyState_[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//���͉����ĂȂ��āA�O��͉����Ă�
		if (!(keyState_[keyCode] & 0x80) && (prevKeyState_[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsMouseButton(int buttonCode)
	{
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if ((mouseState_.rgbButtons[buttonCode] & 0x80) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
			
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonUp(int buttonCode)
	{
		//���͉����ĂȂ��āA�O��͉����Ă�
		if (!(mouseState_.rgbButtons[buttonCode] & 0x80) && (prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput_);
		SAFE_RELEASE(pKeyDevice_);
	}

	XMFLOAT3 GetMousePosition()
	{
		return mousePosition_;
	}

	XMFLOAT3 GetMouseMove()
	{
		return XMFLOAT3(mouseState_.lX, mouseState_.lY, mouseState_.lZ);
	}
	void SetMousePosition(int x, int y)
	{
		mousePosition_.x = x;
		mousePosition_.y = y;
		std::string resStr = std::to_string(x) + "," + std::to_string(y)+"\n";
		OutputDebugString(resStr.c_str());
	}
	
}