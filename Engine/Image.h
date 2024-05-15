#pragma once

#include <vector>
#include <string>
#include<limits>
#include "Sprite.h"
#include "Transform.h"
static std::string ASSET_PATH("../Assets/");//�\�[�X�t�@�C������̃p�X
enum PLACEMENT { LEFT, RIGHT, UP, DOWN };
enum AXIS{X,Y};
//-----------------------------------------------------------
//2D�摜���Ǘ�����
//-----------------------------------------------------------
namespace Image
{
	//�摜���
	struct ImageData
	{
		//�t�@�C����
		std::string fileName;

		//���[�h�����摜�f�[�^�̃A�h���X
		Sprite*		pSprite;

		//�؂蔲���͈�
		RECT		rect;

		//�A���t�@
		float		alpha;

		//�s��
		Transform transform;

		//�R���X�g���N�^
		ImageData() : pSprite(nullptr)
		{
			fileName = "";
			alpha = 1.0f;
			pSprite = nullptr;
		}
	};


	//������
	void Initialize();

	//�摜�����[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̉摜�f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//�`��
	//�����Fhandle	�`�悵�����摜�̔ԍ�
	//�����Fmatrix	���[���h�s��
	void Draw(int handle);

	//�C�ӂ̉摜���J��
	//�����Fhandle	�J�����������f���̔ԍ�
	void Release(int handle);

	//�S�Ẳ摜�����
	//�i�V�[�����؂�ւ��Ƃ��͕K�����s�j
	void AllRelease();

	//�؂蔲���͈͂̐ݒ�
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Fx		�؂蔲�������͈͂̍��[�w���W
	//�����Fy		�؂蔲�������͈͂̏�[�x���W
	//�����Fwidth	�؂蔲�������͈͂̕�
	//�����Fheight	�؂蔲�������͈͂̍���
	void SetRect(int handle, int x, int y, int width, int height);

	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	void ResetRect(int handle);

	//�A���t�@�l���w��
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Falpha �A���t�@�l�i�s�����x�j�@0�`255�Ŏw��
	void SetAlpha(int handle, int alpha);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int handle, Transform& transform);


	//���[���h�s��̎擾
	//�����Fhandle	�m�肽���摜�̔ԍ�
	//�ߒl�F���[���h�s��
	XMMATRIX GetMatrix(int handle);
	
	
	///~~~~~~~~~~~��������g��~~~~~~~~~~~///
	
	/// <summary>
	/// ���K���f�o�C�X���W�n�̒l����X�N���[�����W�n�̒l�ɕϊ�
	/// </summary>
	/// <param name="pos">NDC��XMFLOAT3</param>
	/// <returns>Px�P�ʂɕϊ�����XMFLOAT3</returns>
	XMFLOAT3 toPixel(const XMFLOAT3& pos);
	/// <summary>
	/// ���K���f�o�C�X���W�n�̒l����X�N���[�����W�n�̒l�ɕϊ�
	/// </summary>
	/// <param name="pos">NDC��XMFLOAT3��X or Y</param>
	/// <param name="axis">X��Y��</param>
	/// <returns>Px�P�ʂɕϊ������ɕϊ�����float</returns>
	float toPixel(const float& pos, const AXIS& axis);
	
	/// <summary>
	/// �X�N���[�����W�n�̒l���琳�K���f�o�C�X���W�n�̒l�ɕϊ�
	/// </summary>
	/// <param name="pixel">�s�N�Z���P��</param>
	/// <returns>NDC�ɕϊ��������W</returns>
	XMFLOAT3 toPos(XMFLOAT3 pixel);
	/// <summary>
	/// �X�N���[�����W�n�̒l���琳�K���f�o�C�X���W�n�̒l�ɕϊ�
	/// </summary>
	/// <param name="pixel">�s�N�Z���P��</param>
	/// <returns>NDC�ɕϊ��������W</returns>
	float toPos(float pixel, AXIS axis);

	constexpr float UNSPECIFIED = std::numeric_limits<float>::quiet_NaN();
	/// <summary>
	/// �摜��C�ӈʒu�ɍ��킹���ʒu��Ԃ�
	/// �摜�T�C�Y�͌��݂�Rect����ш�����scale���Q�Ƃ���
	/// </summary>
	/// <param name="handle">�摜�̔ԍ�</param>
	/// <param name="placement">���킹��������</param>
	/// <param name="specifiedPos">���킹����X or Y�̃s�N�Z��(�f�t�H���g�͉�ʒ[�A�ȗ��s�̏ꍇ��UNSPECIFIED������)</param>
	/// <param name="scale">�l������X or Y�̃X�P�[��(�f�t�H���g��1)</param>
	/// <returns>�����ɉ�����������X or Y</returns>
	float AlignImage(const int& handle, const PLACEMENT& placement, float specifiedPos= UNSPECIFIED,float scale=1.0f);

	bool isMouseOver(int handle);

}