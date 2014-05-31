/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 NonLinear Rendering Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>



#include "RenderingEngine\NLRE.h"

LPCTSTR WndClassName = L"mainWindow";
HWND hwnd = NULL;
int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);

RECT clientRect;
float clientCenterX = 0.0f;
float clientCenterY = 0.0f;
float mouseJitter = 0.0001f;

NLRE* nlre = NULL;

void debugCallback(char text[]);
void consoleCallback(char text[]);
void errorCallback(NLRE_Log::ErrorFlag flag, char text[]);
bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
int messageloop();
void ReleaseResources();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nShowCmd)
{
	//creates a console window
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);


	if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	NLRE_Log::registerErrorCallback(errorCallback);
	NLRE_Log::registerConsoleCallback(debugCallback);
	NLRE_Log::registerDebugCallback(debugCallback);

	GetClientRect(hwnd, &clientRect);
	clientCenterX = (clientRect.right - clientRect.left) / 2;
	clientCenterY = (clientRect.bottom - clientRect.top) / 2;

	SetCursorPos(clientCenterX, clientCenterY);
	try
	{
		nlre = new NLRE(hwnd, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	}
	catch (std::exception& e)
	{
		MessageBox(0, L"NLRE failed to initialize",
			L"Error", MB_OK);
		nlre = NULL;
		return 0;
	}

	//nlre->getAssetImporter()->enableBuiltInTexturePath(false);
	//nlre->getAssetImporter()->setTextureResourcePath(L"D:\\3DModels\\Altair Model\\tex\\");

	std::wstring path = L"D:\\3DModels\\Altair Model\\altair2.dae";
	//std::wstring path = L"C:\\Users\\Alex\\Desktop\\2teapot.dae";
	nlre->importAsset(path);

	/*
	nlre->getAssetImporter()->enableBuiltInTexturePath(false);
	nlre->getAssetImporter()->setTextureResourcePath(L"D:\\3DModels\\Crytek Sponza Scene\\textures\\");
	std::wstring path = L"D:\\3DModels\\Crytek Sponza Scene\\sponza.dae";
	nlre->importAsset(path);
	*/

	//std::wstring path = L"C:\\Users\\Alex\\Desktop\\olympic_ring.dae";
	//nlre->importAsset(path);
	//path = L"C:\\Users\\Alex\\Desktop\\torus3.dae";
	//nlre->importAsset(path);
	//path = L"C:\\Users\\Alex\\Desktop\\torus4.dae";
	//nlre->importAsset(path);
	//path = L"C:\\Users\\Alex\\Desktop\\torus5.dae";
	//nlre->importAsset(path);

	//path = L"C:\\Users\\Alex\\Desktop\\sphere.dae";
	//nlre->importAsset(path);
	messageloop();

	ReleaseResources();



	//destroys console window
	fclose(stdout);
	FreeConsole();

	return 0;
}

void ReleaseResources()
{
	NLRE_Log::unregisterConsoleCallbackAll();
	NLRE_Log::unregisterDebugCallbackAll();
	NLRE_Log::unregisterErrorCallbackAll();

	delete nlre;
}

bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
{
	typedef struct _WNDCLASS {
		UINT cbSize;
		UINT style;
		WNDPROC lpfnWndProc;
		int cbClsExtra;
		int cbWndExtra;
		HANDLE hInstance;
		HICON hIcon;
		HCURSOR hCursor;
		HBRUSH hbrBackground;
		LPCTSTR lpszMenuName;
		LPCTSTR lpszClassName;
	} WNDCLASS;

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error registering class",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	hwnd = CreateWindowEx(
		NULL,
		WndClassName,
		L"NonLinear Rendering Engine Test",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hwnd)
	{
		MessageBox(NULL, L"Error creating window",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);

	return true;
}


int messageloop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	int counter = 0;

	while (true)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (GetAsyncKeyState('W'))
		{
			nlre->getSceneManager()->cameraMoveForward();
		}
		if (GetAsyncKeyState('S'))
		{
			nlre->getSceneManager()->cameraMoveBackward();
		}
		if (GetAsyncKeyState('D'))
		{
			nlre->getSceneManager()->cameraMoveRight();
		}
		if (GetAsyncKeyState('A'))
		{
			nlre->getSceneManager()->cameraMoveLeft();
		}
		if (GetAsyncKeyState('E'))
		{
			nlre->getSceneManager()->cameraMoveUp();
		}
		if (GetAsyncKeyState('Q'))
		{
			nlre->getSceneManager()->cameraMoveDown();
		}
		if (GetAsyncKeyState('R'))
		{
			nlre->getSceneManager()->cameraReset();
		}

		if (GetActiveWindow() == hwnd)
		{
			POINT mousePoint;
			GetCursorPos(&mousePoint);

			float distX = (float)mousePoint.x - clientCenterX;
			float distY = (float)mousePoint.y - clientCenterY;

			if (pow(distX, 2.0) > mouseJitter || pow(distY, 2.0) > mouseJitter)
			{
				NLE_VECTOR velocity = NLEMath::NLEVectorSet(distX, distY, 0.0f, 0.0f);
				velocity = NLEMath::NLEVector4Normalize(velocity);
				nlre->getSceneManager()->cameraRotate(NLEMath::NLEVectorGetX(velocity), NLEMath::NLEVectorGetY(velocity));
				SetCursorPos(clientCenterX, clientCenterY);
			}

			nlre->getSceneManager()->cameraUpdate();
			nlre->render();
			counter++;
			if (counter == 20000)
			{
				printf("Rendering");
				counter = 0;
			}
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void errorCallback(NLRE_Log::ErrorFlag flag, char text[])
{
	printf(text);
	printf("\n");
}

void debugCallback(char text[])
{
	printf(text);
	printf("\n");
}

void consoleCallback(char text[])
{
	printf(text);
	printf("\n");
}