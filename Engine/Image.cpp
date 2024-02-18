#include "Image.h"
#include"global.h"

namespace Image {
    std::vector<ImageData*> imageList_;
	bool ExistHandle(int handle) { return (0<=handle  && handle < imageList_.size()); }
}
int Image::Load(std::string fileName)
{
	ImageData* pData = new ImageData;
	pData->fileName_ = fileName;
	pData->pSprite_ = nullptr;

	for (auto& e : imageList_)
	{
		if (e&&e->fileName_ == fileName)
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
	imageList_.at(hPict)->transform_.Calculation();
	imageList_.at(hPict)->pSprite_->Draw(imageList_.at(hPict)->transform_,imageList_.at(hPict)->size);
}

void Image::Release(int hPict)
{
	if (!ExistHandle(hPict))
		return;

	bool isReffered = false;
	for (int i = 0; i < imageList_.size(); i++)
	{
		//‚·‚Å‚ÉŠJ‚¢‚Ä‚¢‚éê‡
		if (imageList_.at(i) != nullptr && i != hPict && imageList_.at(i)->pSprite_ == imageList_.at(hPict)->pSprite_)
		{
			isReffered= true;
			break;
		}
	}

	//Žg‚Á‚Ä‚È‚¯‚ê‚Îƒ‚ƒfƒ‹‰ð•ú
	if (isReffered == false)
	{
		SAFE_DELETE(imageList_.at(hPict)->pSprite_);
	}
	SAFE_DELETE(imageList_.at(hPict));
}

void Image::ReleaseAll()
{
	for (int i = 0; i < imageList_.size(); i++)
	{
		Release(i);
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
