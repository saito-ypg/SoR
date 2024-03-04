#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include<cstdlib>

#include<DirectXCollision.h>
#include"Engine/Direct3D.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/Image.h"
#include"Engine/RootJob.h"
#include <crtdbg.h>

const char* WIN_CLASS_NAME = "SampleGame";
const char* GAME_TITLE = "�T���v���Q�[��";
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���
const DWORD DELTA_MAX = 333;
RootJob* pRootJob = nullptr;

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 303;
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;		               //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;          //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j


	RegisterClassEx(&wc);  //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����


	//�E�B���h�E���쐬

	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		GAME_TITLE,     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW-WS_THICKFRAME, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                 //�E�B���h�E��
		winH,                 //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);


	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
	if (FAILED(hr))
	{
		PostQuitMessage(0);

	}//�v���O�����I��


	hr = Input::Initialize(hWnd);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "���͂̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0);
	}

	Camera::Initialize();

	pRootJob = new RootJob(nullptr);//GameObject�؍\���̍ŏ�ʂ̂��߁A�e����
	pRootJob->Initialize();

	//���b�Z�[�W���[�v�i�����N����̂�҂j

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			timeBeginPeriod(1);
			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			static DWORD countFps = 0;
			static DWORD lastUpdateTime = nowTime;
			if (nowTime - startTime >= 1000)
			{
				char str[16];
				wsprintf(str, "%u", countFps);

				SetWindowText(hWnd, str);

				countFps = 0;
				startTime = nowTime;
			}
			DWORD diff = nowTime - lastUpdateTime;
			if ((diff) * 60 <= 1000.0f)
			{
				continue;
			}
			lastUpdateTime = nowTime;
			countFps++;

			timeEndPeriod(1);

			//�Q�[���̏���
			//�J�����X�V
			Camera::Update();
			//���͂̏���
			Input::Update();
			
			pRootJob->UpdateSub((float)(diff<DELTA_MAX?diff:DELTA_MAX));

			//�`��
			Direct3D::BeginDraw();

			//���[�g�W���u���炷�ׂĂ̎q�I�u�W�F�N�g��draw���Ă�
			pRootJob->DrawSub();

			Direct3D::EndDraw();
		}
	}
	Model::ReleaseAll();
	Image::ReleaseAll();
	pRootJob->ReleaseSub();
	SAFE_DELETE(pRootJob);

	Input::Release();
	Direct3D::Release();


	return 0;
}



//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);//�ǂ̃P�[�X�ɂ����Ă͂܂�Ȃ��ꍇ�A�f�t�H���g�̓���������

}
