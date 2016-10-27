#pragma once

#include <Windows.h>
#include <d2d1_1.h>

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
	
public:
	Graphics();
	~Graphics();

	bool init(HWND windowHandle);

	ID2D1RenderTarget* getRenderTarget()
	{
		return renderTarget;
	}

	void beginDraw()
	{
		renderTarget->BeginDraw();
	}
	void endDraw()
	{
		renderTarget->EndDraw();
	}

	void clearScreen(float r, float g, float b);
	void drawCircle(float x, float y, float radius, float r, float g, float b, float a);

	void fillSquare(float x, float y, int gridSize, const D2D1_COLOR_F& colour);
	void drawGrid(int gridSize, const D2D1_COLOR_F& colour);
};