#include "SpriteSheet.h"



SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* graphics_)
{
	graphics = graphics_;
	bmp = nullptr;
	HRESULT hr;

	// Create interface
	IWICImagingFactory* wicFactory = nullptr;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	if (hr != S_OK)
	{
		// Do something
	}

	// Decode file format
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&wicDecoder);

	if (hr != S_OK)
	{
		// Do something
	}

	// Obtain frame
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	if (hr != S_OK)
	{
		// Do something
	}

	// Create converter
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	if (hr != S_OK)
	{
		// Do something
	}

	// Setup converter
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	if (hr != S_OK)
	{
		// Do something
	}

	// Use converter to load the image into our bitmap variable
	graphics->getRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp);

	// Free memory
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spritesAcross = 1;
}

SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* graphics_, int spriteWidth, int spriteHeight):
	SpriteSheet(filename, graphics_)
{
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->spritesAcross = (int)bmp->GetSize().width / spriteWidth;
}

SpriteSheet::~SpriteSheet()
{
	if (bmp)
	{
		bmp->Release();
	}
}

void SpriteSheet::draw()
{
	graphics->getRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height),	// Destination rectangle
		1.0f,												// Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height)	// Source rectangle
	);
}

void SpriteSheet::draw(int index, float x, float y)
{
	D2D1_RECT_F source = D2D1::RectF(
		(float)((index % spritesAcross) * spriteWidth),
		(float)((index / spritesAcross) * spriteHeight),
		(float)((index % spritesAcross) * spriteWidth) + spriteWidth,
		(float)((index / spritesAcross) * spriteHeight) + spriteHeight);

	D2D1_RECT_F destination = D2D1::RectF(
		x, y,
		x + spriteWidth,
		y + spriteHeight
	);

	graphics->getRenderTarget()->DrawBitmap(
		bmp,
		destination,
		1.0f,												// Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		source
	);
}