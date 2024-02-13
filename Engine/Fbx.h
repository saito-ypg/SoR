#pragma once
#pragma warning(once:4099)
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include<memory>
#include "Transform.h"
#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

class Texture;
struct RayCastData
{
	XMFLOAT4 start;
	XMFLOAT4 dir;
	bool hit;
	float dist;
	RayCastData() { start = { 0,0,0,0 }, dir = { 0,0,0,0 }; dist = FLT_MAX; hit = false; }
};

class Fbx
{
private:
	//�}�e���A��
	struct MATERIAL
	{
		Texture*	pTexture;
		XMFLOAT4	diffuse;
	};
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
		int			isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	
	VERTEX* pVertices_;//���_�z��
	int** ppIndex_;
	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** ppIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;//�}�e���A���̃|�C���^�B��Ŕz��ɂȂ�\��
	int* indexCount_;
public:

	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	void RayCast(RayCastData& raydata);


private:
	void PassDataToCB(Transform transform,int i);
	void SetBufferToPipeline(int i);
	//���_�o�b�t�@����
	HRESULT	InitVertex(fbxsdk::FbxMesh* mesh);
	HRESULT	InitIndex(fbxsdk::FbxMesh* mesh);
	HRESULT InitConstantBuffer();	//�R���X�^���g�o�b�t�@����
	HRESULT InitMaterial(fbxsdk::FbxNode* pNode);
};