#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

const int width = 640;
const int height = 250;

VOID OnPaint(HDC hdc)
{
	Graphics    graphics(hdc);
	SolidBrush  brush(Color(255, 0, 0, 255));
	FontFamily  fontFamily(L"Consolas");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(10.0f, 20.0f);

	graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wClass;
	HWND hWindow;
	MSG uMessage;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	memset(&wClass, 0, sizeof(WNDCLASSEX));

	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	wClass.hCursor = LoadCursor(nullptr, IDC_APPSTARTING);
	wClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WindowProc;
	wClass.lpszClassName = "sag.osiris clients launcher";

	RegisterClassEx(&wClass);

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	hWindow = CreateWindow(
		wClass.lpszClassName,
		"launcher",
		WS_POPUP,
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - height) / 2,
		width,
		height,
		nullptr,
		nullptr,
		nullptr,
		nullptr);

	ShowWindow(hWindow, nCmdShow);

	while (GetMessage(&uMessage, hWindow, NULL, NULL))
	{
		TranslateMessage(&uMessage);
		DispatchMessage(&uMessage);
	}

	GdiplusShutdown(gdiplusToken);

	return uMessage.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;

	switch (uMsg)
	{
	case WM_CREATE:

		CreateWindow("BUTTON", "X", WS_CHILD | WS_VISIBLE, 50, 50, 32, 32, hwnd, HMENU(1), nullptr, nullptr);
		
		break;
		
	case WM_COMMAND:

		switch(wParam)
		{
		case 1:
			ExitProcess(ERROR_SUCCESS);
		}

		break;

	case WM_CLOSE: ExitProcess(ERROR_SUCCESS);

	case WM_PAINT:

		hDC = BeginPaint(hwnd, &ps);
		OnPaint(hDC);
		EndPaint(hwnd, &ps);

		break;

	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
