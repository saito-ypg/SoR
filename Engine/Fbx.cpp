#include<DirectXCollision.h>
#include "Fbx.h"
#include"Direct3D.h"
#include"Camera.h"
#include"Texture.h"

Fbx::Fbx() :pVertexBuffer_(nullptr), ppIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pMaterialList_(nullptr), pVertices_(nullptr),ppIndex_(nullptr), vertexCount_(0), polygonCount_(0), materialCount_(0), indexCount_(nullptr)
{
}

Fbx::~Fbx()
{
	Release();
}

HRESULT Fbx::Load(std::string fileName)
{
	//�}�l�[�W���𐶐�
	FbxManager* pFbxManager = FbxManager::Create();

	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	//�C���|�[�^�[�𐶐�
	FbxString FileName(fileName.c_str());
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	if(!fbxImporter->Initialize(FileName.Buffer(), -1, pFbxManager->GetIOSettings()))
	{
		string e = fbxImporter->GetStatus().GetErrorString();
		MessageBox(nullptr,e.c_str(), "�C���|�[�^�[���������s", MB_OK);
		return E_FAIL;
	}


	if(!fbxImporter->Import(pFbxScene))//�ǂݍ��ݎ��s
	{
		string e = fbxImporter->GetStatus().GetErrorString();
		MessageBox(nullptr, e.c_str(), "�t�@�C���ǂݍ��ݎ��s", MB_OK);
		return E_FAIL;
	}
	fbxImporter->Destroy();

	//���b�V�������擾
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//�e���̌����擾
	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
	polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount();//�}�e���A���̐�


	//���݂̃J�����g�f�B���N�g�����o���Ă���
	char curDir[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, curDir);

	//������fileName����f�B���N�g���������擾
	char dir[MAX_PATH];
	_splitpath_s(fileName.c_str(), nullptr, 0, dir, _MAX_DIR, nullptr, 0, nullptr, 0);

	//�J�����g�f�B���N�g���ύX
	SetCurrentDirectory(dir);

	HRESULT hr;
	hr=InitVertex(mesh);		//���_�o�b�t�@����
	if (FAILED(hr))
	{
		MessageBox(nullptr, "���_�o�b�t�@�̏������Ɏ��s���܂���", "FBX�G���[", MB_OK);
		return hr;
	}
	hr=InitIndex(mesh);		//�C���f�b�N�X�o�b�t�@����
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̏������Ɏ��s���܂���", "FBX�G���[", MB_OK);
		return hr;
	}
	hr=InitConstantBuffer();	//�R���X�^���g�o�b�t�@����
	if (FAILED(hr))
	{
		MessageBox(nullptr, "���_�̏������Ɏ��s���܂���", "FBX�G���[", MB_OK);
		return hr;
	}
	hr=InitMaterial(pNode);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�}�e���A���̓ǂݍ��݂Ɏ��s���܂���", "FBX�G���[", MB_OK);
		return hr;
	}

	//�J�����g�f�B���N�g�������ɖ߂�
	char result[_MAX_DIR + 4];
	wsprintf(result, "%s", curDir);
	SetCurrentDirectory(result);

	//�}�l�[�W�����
	pFbxManager->Destroy();
	return S_OK;
}

void Fbx::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_3D);
	transform.Calculation();//�g�����X�t�H�[�����v�Z
	//�R���X�^���g�o�b�t�@�ɏ���n��
	
	for (int i = 0; i < materialCount_; i++)
	{
		CONSTANT_BUFFER cb;
		cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
		cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());
		cb.isTexture = pMaterialList_[i].pTexture != nullptr;
		cb.diffuseColor = pMaterialList_[i].diffuse;

		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
		if (pMaterialList_[i].pTexture)
		{
		
			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
			ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
			Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
		}
		

		Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ
		//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�R���X�^���g�o�b�t�@���p�C�v���C���ɃZ�b�g
		//���_�o�b�t�@
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
		// �C���f�b�N�X�o�b�t�@�[���Z�b�g
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext_->IASetIndexBuffer(ppIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//�R���X�^���g�o�b�t�@
		Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
		Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	
		//�`��
		Direct3D::pContext_->DrawIndexed(indexCount_[i], 0, 0);
	}
}

void Fbx::Release()
{

	SAFE_RELEASE(pVertexBuffer_);
	for (int i = 0; i < materialCount_; i++)
	{
		SAFE_RELEASE(ppIndexBuffer_[i]);
		SAFE_DELETE(ppIndex_[i]);
		SAFE_DELETE(pMaterialList_[i].pTexture);
	}
	
	SAFE_DELETE_ARRAY(ppIndex_);
	SAFE_DELETE_ARRAY(indexCount_);
	SAFE_DELETE_ARRAY(ppIndexBuffer_);
	SAFE_DELETE_ARRAY(pMaterialList_);

	SAFE_DELETE_ARRAY(pVertices_);
	SAFE_RELEASE(pConstantBuffer_);
}

void Fbx::RayCast(RayCastData& rayData)
{
	for (int material = 0; material < materialCount_; material++)
	{
		for (int poly = 0; poly < indexCount_[material]/3; poly++)
		{
			XMVECTOR v0 = pVertices_[ppIndex_[material][poly * 3]].position;
			XMVECTOR v1 = pVertices_[ppIndex_[material][poly * 3+1]].position;
			XMVECTOR v2 = pVertices_[ppIndex_[material][poly * 3+2]].position;
			XMVECTOR start =XMLoadFloat4( &rayData.start);
			XMVECTOR dir =XMVector3Normalize(XMLoadFloat4(&rayData.dir));
			rayData.hit = DirectX::TriangleTests::Intersects(start,dir,v0, v1, v2,rayData.dist);
			if (rayData.hit)
			{
				return;
			}
		}
	}
}

//���_�o�b�t�@����
HRESULT Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
{

	pVertices_ = new VERTEX[vertexCount_];

	//�S�|���S��
	for (int poly = 0; poly < polygonCount_; poly++)
	{
		//3���_��
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//���ׂ钸�_�̔ԍ�
			int index = mesh->GetPolygonVertex(poly, vertex);

			//���_�̈ʒu
			FbxVector4 pos = mesh->GetControlPointAt(index);
			pVertices_[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//���_��UV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			pVertices_[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//���_�̖@��
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//���Ԗڂ̃|���S���́A���Ԗڂ̒��_�̖@�����Q�b�g
			pVertices_[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}
	}
	// ���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = vertexCount_ * sizeof(VERTEX);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = pVertices_;
	return Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);


}

//�C���f�b�N�X�o�b�t�@����
HRESULT Fbx::InitIndex(fbxsdk::FbxMesh* mesh)
{
	ppIndexBuffer_ = new ID3D11Buffer*[materialCount_];
	indexCount_ = new int[materialCount_];
	ppIndex_ = new int* [materialCount_];
	const int indexes = polygonCount_ * 3;
	for (int i = 0; i < materialCount_; i++)
	{
		ppIndex_[i] = new int[indexes];
		int count = 0;
		
		//�S�|���S��
		for (int poly = 0; poly < polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i)
			{//3���_��
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					ppIndex_ [i][count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}

		}
		indexCount_[i] = count;
		
		// �C���f�b�N�X�o�b�t�@�𐶐�����
		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = polygonCount_ * 3 * sizeof(int);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = ppIndex_[i];
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		HRESULT hr=Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &ppIndexBuffer_[i]);
		if(FAILED(hr))
		{
			return hr;
		}
	}
	return S_OK;
}

HRESULT Fbx::InitConstantBuffer()//�R���X�^���g�o�b�t�@����
{
	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	return  Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);

}

void Fbx::PassDataToCB(Transform transform,int i)
{
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
	
		ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
		Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
		ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
		Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
	
	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ
}

void Fbx::SetBufferToPipeline(int i)
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(ppIndexBuffer_[i], DXGI_FORMAT_R32_UINT, offset);
		
	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
}

HRESULT Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = new Fbx::MATERIAL[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		//i�Ԗڂ̃}�e���A�������擾
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//�e�N�X�`�����
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//�e�N�X�`���̐���
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//�e�N�X�`������
		if (fileTextureCount>0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			string textureFilePath = textureInfo->GetRelativeFileName();

			//�t�@�C����+�g�������ɂ���
			char name[_MAX_FNAME];	//�t�@�C����
			char ext[_MAX_EXT];	//�g���q
			_splitpath_s(textureFilePath.c_str(), nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			wsprintf(name, "%s%s", name, ext);

			//�t�@�C������e�N�X�`���쐬
			pMaterialList_[i].pTexture = new Texture;
			HRESULT hr=pMaterialList_[i].pTexture->Load(name);
			if(FAILED(hr))
			{
				return hr;
			}

		}
		//�e�N�X�`������
		else
		{
			pMaterialList_[i].pTexture= nullptr;

			//�}�e���A���̐F
			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			
			FbxDouble3  diffuse = pMaterial->Diffuse;
			pMaterialList_[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
		}
	}
	return S_OK;
}
