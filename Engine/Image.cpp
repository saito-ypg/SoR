#include "Image.h"
#include"global.h"
#include"Debug.h"
namespace Image {
    std::vector<ImageData*> imageList_;
	bool ExistHandle(int handle) { return (handle >= 0 && handle < imageList_.size()); }
}
int Image::Load(std::string fileName)
{
	Debug::Log((int)sizeof(ImageData));
	ImageData* pData = new ImageData;
	pData->fileName_ = fileName;
	pData->pSprite_ = nullptr;

	for (auto& e : imageList_)
	{
		if (e->fileName_ == fileName)
		{
			pData->pSprite_ = e->pSprite_;
			break;
		}
	}
	if (pData->pSprite_ == nullptr)
	{
		pData->pSprite_ = new Sprite;
		pData->pSprite_->Initialize(fileName);
	}

	imageList_.push_back(pData);
	int newHandle = (int)imageList_.size() - 1;
	ResetRect(newHandle);
	return newHandle;
}

void Image::SetTransform(int hPict, Transform transform)
{
	if (!ExistHandle(hPict))
		return;
	imageList_.at(hPict)->transform_ = transform;
}

void Image::Draw(int hPict)
{
	if (!ExistHandle(hPict))
		return;
	imageList_.at(hPict)->pSprite_->Draw(imageList_.at(hPict)->transform_,imageList_.at(hPict)->size);
}

void Image::Release(int hPict)
{
	if (!ExistHandle(hPict))
		return;
}

void Image::Release()
{
	bool isReffered = false;
	for (int i = 0; i < imageList_.size(); i++)
	{
		for (int j = i + 1; j < imageList_.size(); j++)
		{
			isExist = true;
			break;
		}
	}

	//Žg‚Á‚Ä‚È‚¯‚ê‚Îƒ‚ƒfƒ‹‰ð•ú
	if (isExist == false)
	{
		SAFE_DELETE(imageList_.at(hPict)->pSprite_);
	}
	SAFE_DELETE(imageList_.at(hPict));
	imageList_.erase(imageList_.begin()+hPict);
}

void Image::ReleaseAll()
{
	
	for (int i = 0; i < imageList_.size(); i++)
	{
		Release(i);/*
		SAFE_DELETE(imageList_.at(i)->pSprite_);
		SAFE_DELETE(imageList_.at(i));*/
	}
	imageList_.clear();
}

void Image::ResetRect(int hPict)
{
	XMFLOAT3 size = imageList_.at(hPict)->pSprite_-> GetTextureSize();
	imageList_.at(hPict)->size.left = 0;
	imageList_.at(hPict)->size.top = 0;
	imageList_.at(hPict)->size.right = (long)size.x;
	imageList_.at(hPict)->size.bottom = (long)size.y;
}
