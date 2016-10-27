#include "Graphics.h"

Graphics::Graphics():
	factory(NULL),
	renderTarget(NULL),
	brush(NULL)
{
}

Graphics::~Graphics()
{
	if (factory)
	{
		factory->Release();
	}

	if (renderTarget)
	{
		renderTarget->Release();
	}

	if (brush)
	{
		brush->Release();
	}
};

bool Graphics::init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK)
	{
		return false;
	}


	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			windowHandle,
			D2D1::SizeU(rect.right, rect.bottom)),
			&renderTarget);

	if (res != S_OK)
	{
		return false;
	}

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	if (res != S_OK)
	{
		return false;
	}

	return true;
}

void Graphics::clearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::drawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
	renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush);
}

void Graphics::fillSquare(float x, float y, int gridSize, const D2D1_COLOR_F& colour)
{
	brush->SetColor(colour);

	renderTarget->FillRectangle(D2D1::RectF(x * gridSize, y * gridSize, (x * gridSize) + gridSize, (y * gridSize) + gridSize), brush);
}

void Graphics::drawGrid(int gridSize, const D2D1_COLOR_F& colour)
{
	brush->SetColor(colour);
	float screenHeight = renderTarget->GetSize().height;
	float screenWidth = renderTarget->GetSize().width;

	for (int i = 0; (i * gridSize) <= screenWidth; ++i)
	{
		renderTarget->DrawLine(D2D1::Point2F(i * gridSize, 0), D2D1::Point2F(i* gridSize, screenHeight), brush);
	}

	for (int i = 0; (i *gridSize) <= screenHeight; ++i)
	{
		renderTarget->DrawLine(D2D1::Point2F(0, i * gridSize), D2D1::Point2F(screenWidth, i * gridSize), brush);
	}
}