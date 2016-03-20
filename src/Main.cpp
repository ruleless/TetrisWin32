#include "common.h"
#include "Tetris.h"
#include "GdiRenderSystem.h"
#include "../res/resource.h"

HWND gWindow = NULL;
TCHAR szTitle[MAX_BUF];
TCHAR szWindowClass[MAX_BUF];

namespace tetris
{
	Tetris *gTetris = NULL;
	RenderSystem *gRenderSystem = NULL;
}

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{	
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_BUF);
	LoadString(hInstance, IDC_BLOCK, szWindowClass, MAX_BUF);
	MyRegisterClass(hInstance);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	HACCEL hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_BLOCK);

	tetris::gTetris = new tetris::Tetris();
	tetris::gRenderSystem = new tetris::GdiRenderSystem(gWindow, hInstance);
	tetris::gTetris->initialise();
	tetris::gTetris->start();
	
	// Main message loop:
	DWORD dwLastTime = timeGetTime();
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while (msg.message != WM_QUIT) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD dwCurTime = (float)timeGetTime();
			static DWORD s_delta = (DWORD)(1000.0/tetris::GameFps);

			if (dwCurTime - dwLastTime > s_delta)
			{
				float fDelta = (dwCurTime - dwLastTime) * 0.001;

				tetris::gTetris->update(fDelta);
				tetris::gRenderSystem->renderOneFrame(fDelta);

				dwLastTime = dwCurTime;
			}
		}
	}

	tetris::gTetris->finalise();
	delete tetris::gRenderSystem;
	delete tetris::gTetris;
	
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX); 
	
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_BLOCK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(0,0,0)));
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{	
	gWindow = CreateWindow(
		szWindowClass, 
		szTitle, 
		(
		WS_OVERLAPPED     |
		WS_CAPTION        |
		WS_SYSMENU        |
		WS_THICKFRAME     |
		WS_MINIMIZEBOX
		// WS_MAXIMIZEBOX
		),
		CW_USEDEFAULT, 
		0, CW_USEDEFAULT, 0, 
		NULL, NULL, hInstance, NULL);
	
	if (!gWindow)
	{
		return FALSE;
	}
	
	ShowWindow(gWindow, nCmdShow);

	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	int w = 800, h = 600;
	MoveWindow(gWindow, (scrWidth-w)>>1, (scrHeight-h)>>1, w, h, FALSE);
	
	UpdateWindow(gWindow);
	
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message) 
	{
	case WM_ERASEBKGND:
		break;
	case WM_CREATE:
		{
			break;
		}
	case WM_SIZE:
		{
			break;
		}
	case WM_TIMER:
		{
			break;
		}
	case WM_KEYDOWN:
		if (tetris::gTetris)
		{
			tetris::gTetris->injectKeyDown((char)wParam);
		}
		break;
	case WM_KEYUP:
		{
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_NCHITTEST:
	// case WM_NCLBUTTONDOWN:
		break;
	default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}
