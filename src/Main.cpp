// Block.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "../resource.h"
#include "../Valuable.h"
#include <time.h>
#include "../Fuc.h"


// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BLOCK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_BLOCK);
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
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
	HWND hWnd;
	
	hInst = hInstance; // Store instance handle in our global variable
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,j,k;
	static int nn=0;
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message) 
	{
	case WM_ERASEBKGND:
		break;
	case WM_CREATE:
		{
			flagPause=false;
			gameOver=false;
			flagTimer=false;
			GetClientRect(hWnd,&rect);
			cBlock=rect.bottom/25;
			workRect.left=cBlock*3;
			workRect.top=cBlock*3;
			workRect.right=workRect.left+15*cBlock;
			workRect.bottom=workRect.top+20*cBlock;

			showRect.left=workRect.right+2*cBlock;
			showRect.top=workRect.top+2*cBlock;
			showRect.right=showRect.left+5*cBlock;
			showRect.bottom=showRect.top+5*cBlock;

			levelRect.left=showRect.left;
			levelRect.top=showRect.bottom+2*cBlock;
			levelRect.right=levelRect.left+5*cBlock;
			levelRect.bottom=levelRect.top+2*cBlock;

			scoreRect.left=levelRect.left;
			scoreRect.top=levelRect.bottom+2*cBlock;
			scoreRect.right=scoreRect.left+5*cBlock;
			scoreRect.bottom=scoreRect.top+2*cBlock;

			int cx=workRect.right-workRect.left;
			int cy=workRect.bottom-workRect.top;
			pauseRect.left=workRect.left+cx/2;
			pauseRect.top=workRect.top+cy/2-1*cBlock;
			pauseRect.right=pauseRect.left+6*cBlock;
			pauseRect.bottom=pauseRect.top+3*cBlock;
			
			InitGame(hWnd);
			break;
		}
	case WM_SIZE:
		{
			GetClientRect(hWnd,&rect);
			cBlock=rect.bottom/25;
			workRect.left=cBlock*3;
			workRect.top=cBlock*3;
			workRect.right=workRect.left+15*cBlock;
			workRect.bottom=workRect.top+20*cBlock;

			showRect.left=workRect.right+2*cBlock;
			showRect.top=workRect.top+2*cBlock;
			showRect.right=showRect.left+5*cBlock;
			showRect.bottom=showRect.top+5*cBlock;

			levelRect.left=showRect.left;
			levelRect.top=showRect.bottom+2*cBlock;
			levelRect.right=levelRect.left+5*cBlock;
			levelRect.bottom=levelRect.top+2*cBlock;

			scoreRect.left=levelRect.left;
			scoreRect.top=levelRect.bottom+2*cBlock;
			scoreRect.right=scoreRect.left+5*cBlock;
			scoreRect.bottom=scoreRect.top+2*cBlock;

			int cx=workRect.right-workRect.left;
			int cy=workRect.bottom-workRect.top;
			pauseRect.left=workRect.left+cx/2;
			pauseRect.top=workRect.top+cy/2-1*cBlock;
			pauseRect.right=pauseRect.left+6*cBlock;
			pauseRect.bottom=pauseRect.top+3*cBlock;
			
			for(i=3;i<23;i++)
			{
				for(j=0;j<15;j++)
				{
					m_grid[i][j].left=workRect.left+j*cBlock;
					m_grid[i][j].top=workRect.top+(i-3)*cBlock;
					m_grid[i][j].right=workRect.left+(j+1)*cBlock;
					m_grid[i][j].bottom=workRect.top+(i-2)*cBlock;
				}
			}
			break;
		}
	case WM_TIMER:
		{
			TimeFun(hWnd);
			break;
		}
	case WM_KEYDOWN:
		{
			if(gameOver)break;
			int left=40,top=40,right=0,bottom=0;
			if(wParam=='D')
			{
				if(flagPause)break;
				if(rightmostj()==14||!checkableright())
					break;
				int i;
				for(i=0;i<4;i++)
				{
					flag[m_block[i].i][m_block[i].j]=false;
					left=( (m_block[i].j<left)?m_block[i].j:left );
					top=( (m_block[i].i<top)?m_block[i].i:top );
					right=( (m_block[i].j>right)?m_block[i].j:right );
					bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
					m_block[i].j++;
				}
				for(i=0;i<4;i++)
				{
					left=( (m_block[i].j<left)?m_block[i].j:left );
					top=( (m_block[i].i<top)?m_block[i].i:top );
					right=( (m_block[i].j>right)?m_block[i].j:right );
					bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
					flag[m_block[i].i][m_block[i].j]=true;
				}
			}
			else if(wParam=='W')
			{
				if(flagPause)
				{
					flagPause=false;
					InvalidateRect(hWnd,&pauseRect,TRUE);
					SetTimer(hWnd,1,m_time,NULL);
				}
				else
				{
					flagPause=true;
					InvalidateRect(hWnd,&pauseRect,TRUE);
					if(timeflag)
					{
						KillTimer(hWnd,1);
					}
				}
				break;
			}
			else if(wParam=='S')
			{
				if(flagPause)break;
				if(flagTimer)break;
				flagTimer=true;
				timeflag=true;
				SetTimer(hWnd,1,15,NULL);
				break;
			}
			else if(wParam=='A')
			{
				if(flagPause)break;
				if(leftmostj()==0||!checkableleft())
					break;
				int i;
				for(i=0;i<4;i++)
				{
					flag[m_block[i].i][m_block[i].j]=false;
					left=( (m_block[i].j<left)?m_block[i].j:left );
					top=( (m_block[i].i<top)?m_block[i].i:top );
					right=( (m_block[i].j>right)?m_block[i].j:right );
					bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
					m_block[i].j--;
				}
				for(i=0;i<4;i++)
				{
					left=( (m_block[i].j<left)?m_block[i].j:left );
					top=( (m_block[i].i<top)?m_block[i].i:top );
					right=( (m_block[i].j>right)?m_block[i].j:right );
					bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
					flag[m_block[i].i][m_block[i].j]=true;
				}
			}
			else if(wParam=='J')
			{
				if(flagPause)break;
				switch(m_n)
				{
				case 0:
					tempa[0].i=m_block[2].i;tempa[0].j=m_block[2].j-2;
					tempa[1].i=m_block[2].i,tempa[1].j=m_block[2].j-1;
					tempa[2].i=m_block[2].i;tempa[2].j=m_block[2].j;
					tempa[3].i=m_block[2].i;tempa[3].j=m_block[2].j+1;
					if(checktempa())
					{
						m_n=1;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 1:
					tempa[0].i=m_block[1].i-2;tempa[0].j=m_block[1].j;
					tempa[1].i=m_block[1].i-1,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[1].i;tempa[2].j=m_block[1].j;
					tempa[3].i=m_block[1].i+1;tempa[3].j=m_block[1].j;
					if(checktempa())
					{
						m_n=0;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 2:
					break;
				case 3:
					tempa[0].i=m_block[2].i;tempa[0].j=m_block[2].j-1;
					tempa[1].i=m_block[2].i,tempa[1].j=m_block[2].j;
					tempa[2].i=m_block[3].i;tempa[2].j=m_block[3].j;
					tempa[3].i=m_block[3].i;tempa[3].j=m_block[3].j+1;
					if(checktempa())
					{
						m_n=4;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 4:
					tempa[0].i=m_block[1].i-1;tempa[0].j=m_block[1].j;
					tempa[1].i=m_block[1].i,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[0].i;tempa[2].j=m_block[0].j;
					tempa[3].i=m_block[0].i+1;tempa[3].j=m_block[0].j;
					if(checktempa())
					{
						m_n=3;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 5:
					tempa[0].i=m_block[2].i;tempa[0].j=m_block[2].j+1;
					tempa[1].i=m_block[2].i,tempa[1].j=m_block[2].j;
					tempa[2].i=m_block[3].i;tempa[2].j=m_block[3].j;
					tempa[3].i=m_block[3].i;tempa[3].j=m_block[3].j-1;
					if(checktempa())
					{
						m_n=6;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					break;
				case 6:
					tempa[0].i=m_block[1].i-1;tempa[0].j=m_block[1].j;
					tempa[1].i=m_block[1].i,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[1].i;tempa[2].j=m_block[1].j+1;
					tempa[3].i=m_block[1].i+1;tempa[3].j=m_block[1].j+1;
					if(checktempa())
					{
						m_n=5;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 7:
					tempa[0].i=m_block[0].i;tempa[0].j=m_block[0].j;
					tempa[1].i=m_block[0].i+1,tempa[1].j=m_block[0].j;
					tempa[2].i=m_block[0].i+2;tempa[2].j=m_block[0].j;
					tempa[3].i=m_block[1].i;tempa[3].j=m_block[1].j;
					if(checktempa())
					{
						m_n=8;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 8:
					tempa[0].i=m_block[3].i;tempa[0].j=m_block[3].j;
					tempa[1].i=m_block[3].i,tempa[1].j=m_block[3].j+1;
					tempa[2].i=m_block[3].i;tempa[2].j=m_block[3].j+2;
					tempa[3].i=m_block[2].i;tempa[3].j=m_block[2].j;
					if(checktempa())
					{
						m_n=9;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					break;
				case 9:
					tempa[0].i=m_block[1].i-1;tempa[0].j=m_block[1].j;
					tempa[1].i=m_block[1].i,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[1].i+1;tempa[2].j=m_block[1].j;
					tempa[3].i=m_block[2].i;tempa[3].j=m_block[2].j;
					if(checktempa())
					{
						m_n=10;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					break;
				case 10:
					tempa[0].i=m_block[0].i;tempa[0].j=m_block[0].j;
					tempa[1].i=m_block[1].i,tempa[1].j=m_block[1].j-1;
					tempa[2].i=m_block[1].i;tempa[2].j=m_block[1].j;
					tempa[3].i=m_block[1].i;tempa[3].j=m_block[1].j+1;
					if(checktempa())
					{
						m_n=7;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 11:
					tempa[0].i=m_block[3].i;tempa[0].j=m_block[3].j;
					tempa[1].i=m_block[3].i,tempa[1].j=m_block[3].j+1;
					tempa[2].i=m_block[3].i;tempa[2].j=m_block[3].j+2;
					tempa[3].i=m_block[3].i+1;tempa[3].j=m_block[3].j;
					if(checktempa())
					{
						m_n=12;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 12:
					tempa[0].i=m_block[0].i-1;tempa[0].j=m_block[0].j;
					tempa[1].i=m_block[0].i,tempa[1].j=m_block[0].j;
					tempa[2].i=m_block[0].i+1;tempa[2].j=m_block[0].j;
					tempa[3].i=m_block[0].i+1;tempa[3].j=m_block[0].j+1;
					if(checktempa())
					{
						m_n=13;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 13:
					tempa[0].i=m_block[3].i;tempa[0].j=m_block[3].j-2;
					tempa[1].i=m_block[3].i,tempa[1].j=m_block[3].j-1;
					tempa[2].i=m_block[3].i;tempa[2].j=m_block[3].j;
					tempa[3].i=m_block[3].i-1;tempa[3].j=m_block[3].j;
					if(checktempa())
					{
						m_n=14;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 14:
					tempa[0].i=m_block[3].i;tempa[0].j=m_block[3].j;
					tempa[1].i=m_block[3].i+1,tempa[1].j=m_block[3].j;
					tempa[2].i=m_block[3].i+2;tempa[2].j=m_block[3].j;
					tempa[3].i=m_block[3].i;tempa[3].j=m_block[3].j-1;
					if(checktempa())
					{
						m_n=11;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 15:
					tempa[0].i=m_block[1].i;tempa[0].j=m_block[1].j-1;
					tempa[1].i=m_block[1].i,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[1].i;tempa[2].j=m_block[1].j+1;
					tempa[3].i=m_block[1].i-1;tempa[3].j=m_block[1].j-1;
					if(checktempa())
					{
						m_n=16;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 16:
					tempa[0].i=m_block[1].i-2;tempa[0].j=m_block[1].j;
					tempa[1].i=m_block[1].i-1,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[1].i;tempa[2].j=m_block[1].j;
					tempa[3].i=m_block[1].i;tempa[3].j=m_block[1].j-1;
					if(checktempa())
					{
						m_n=17;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 17:
					tempa[0].i=m_block[1].i;tempa[0].j=m_block[1].j-1;
					tempa[1].i=m_block[1].i,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[1].i;tempa[2].j=m_block[1].j+1;
					tempa[3].i=m_block[1].i+1;tempa[3].j=m_block[1].j+1;
					if(checktempa())
					{
						m_n=18;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				case 18:
					tempa[0].i=m_block[1].i-1;tempa[0].j=m_block[1].j;
					tempa[1].i=m_block[1].i,tempa[1].j=m_block[1].j;
					tempa[2].i=m_block[1].i+1;tempa[2].j=m_block[1].j;
					tempa[3].i=m_block[1].i-1;tempa[3].j=m_block[1].j+1;
					if(checktempa())
					{
						m_n=15;
						for(i=0;i<4;i++)
						{
							flag[m_block[i].i][m_block[i].j]=false;
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
						}
						for(i=0;i<4;i++)
						{
							m_block[i].i=tempa[i].i;m_block[i].j=tempa[i].j;
						}
						for(i=0;i<4;i++)
						{
							left=( (m_block[i].j<left)?m_block[i].j:left );
							top=( (m_block[i].i<top)?m_block[i].i:top );
							right=( (m_block[i].j>right)?m_block[i].j:right );
							bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );
							flag[m_block[i].i][m_block[i].j]=true;
						}
					}
					else
						goto loop;
					break;
				default:
					break;
				}
			}
			else
			{
				goto loop;
			}
			RECT valRect;
			valRect.left=workRect.left+left*cBlock;
			valRect.top=workRect.top+(top-3)*cBlock;
			valRect.right=workRect.left+(right+1)*cBlock;
			valRect.bottom=workRect.top+(bottom-2)*cBlock;
			InvalidateRect(hWnd,&valRect,TRUE);
loop:		
			break;
		}
	case WM_KEYUP:
		{
			if(flagPause)break;
			if(wParam=='S')
			{
				timeflag=true;
				flagTimer=false;
				SetTimer(hWnd,1,m_time,NULL);
			}
			break;
		}
	case WM_PAINT:
		{
			hdc = GetDC(hWnd);
			//BeginPaint(hWnd, &ps);
			
			HDC hdcmem;
			HBITMAP bmpmem;
			hdcmem=CreateCompatibleDC(hdc);
			bmpmem=CreateCompatibleBitmap(hdc,rect.right-rect.left,rect.bottom-rect.top);		
			SelectObject(hdcmem,bmpmem);

			char szNext[100],szPause[100];
			int iLen;
			HBRUSH hBrush=CreateSolidBrush(RGB(60,50,50));
			DeleteObject(SelectObject(hdcmem,hBrush));//
			Rectangle(hdcmem,rect.left,rect.top,rect.right,rect.bottom);

			hBrush=CreateSolidBrush(RGB(165,188,188));
			DeleteObject(SelectObject(hdcmem,hBrush));//
			Rectangle(hdcmem,workRect.left,workRect.top,workRect.right,workRect.bottom);
			HPEN hPen=CreatePen(PS_SOLID,1,RGB(120,120,120));
			DeleteObject(SelectObject(hdcmem,hPen));//
			for(i=0;i<=15;i++)
			{
				MoveToEx(hdcmem,workRect.left+i*cBlock,workRect.top,NULL);
				LineTo(hdcmem,workRect.left+i*cBlock,workRect.bottom);
			}
			for(i=0;i<=20;i++)
			{
				MoveToEx(hdcmem,workRect.left,workRect.top+cBlock*i,NULL);
				LineTo(hdcmem,workRect.right,workRect.top+cBlock*i);
			}
			hBrush=CreateSolidBrush(RGB(100,160,170));
			DeleteObject(SelectObject(hdcmem,hBrush));

			for(i=3;i<23;i++)
			{
				for(j=0;j<15;j++)
				{
					if(flag[i][j])
					{
						Rectangle(hdcmem,m_grid[i][j].left,m_grid[i][j].top,m_grid[i][j].right,m_grid[i][j].bottom);
					}
				}
			}
			//next
			for(i=0;i<4;i++)
			{
				Rectangle(hdcmem,showRect.left+(m_blockAfter[i].j-8)*cBlock,showRect.top+m_blockAfter[i].i*cBlock,showRect.left+(m_blockAfter[i].j-7)*cBlock,
					showRect.top+(m_blockAfter[i].i+1)*cBlock);
			}
			iLen=wsprintf(szNext,"Next Block:");
			SetBkMode(hdcmem,TRANSPARENT);
			TextOut(hdcmem,showRect.left,showRect.top-2*cBlock,szNext,iLen);

			//levelRect,scoreRect
			char szScore[100],szLevel[100];
			iLen=wsprintf(szLevel,"level : %d",iLevel);
			TextOut(hdcmem,levelRect.left,levelRect.top,szLevel,iLen);
			iLen=wsprintf(szScore,"score : %d",iScore);
			SetBkMode(hdcmem,TRANSPARENT);
			TextOut(hdcmem,scoreRect.left,scoreRect.top,szScore,iLen);
			
			//gameOver?
			if(gameOver)
			{
				iLen=wsprintf(szPause,"Game Over!");
				SetBkMode(hdcmem,TRANSPARENT);
				TextOut(hdcmem,pauseRect.left,pauseRect.top,szPause,iLen);
			}

			//pause?
			if(flagPause)
			{
				iLen=wsprintf(szPause,"Pause!");
				SetBkMode(hdcmem,TRANSPARENT);
				TextOut(hdcmem,pauseRect.left,pauseRect.top,szPause,iLen);
			}
			BitBlt(hdc,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,hdcmem,0,0,SRCCOPY);
			//BitBlt(hdc,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,hdcmem,0,0,SRCCOPY);
			ReleaseDC(hWnd,hdc);
			DeleteDC(hdcmem);
			DeleteObject(bmpmem);
			ValidateRect(hWnd,&rect);
			//EndPaint(hWnd, &ps);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}

void InitGame(HWND hWnd)
{
	srand(time(NULL)%100);
	m_nAfter=rand()%19;
	iLevel=1,iScore=0;
	int i,j;								//初始化网格
	for(i=3;i<23;i++)
	{
		for(j=0;j<15;j++)
		{
			flag[i][j]=false;
			m_grid[i][j].left=workRect.left+j*cBlock;
			m_grid[i][j].top=workRect.top+(i-3)*cBlock;
			m_grid[i][j].right=workRect.left+(j+1)*cBlock;
			m_grid[i][j].bottom=workRect.top+(i-2)*cBlock;
		}
	}
	m_time=300;
	SetTimer(hWnd,1,m_time,NULL);				//设置定时器消息
	timeflag=true;
	UpdateBlock(hWnd);
}

void TimeFun(HWND hWnd)
{
	int i,j,k;
	if( m_block[Maxi()].i==22||!checkabledown() )          //当不能继续下降时
	{
		KillTimer(hWnd,1);
		timeflag=false;
	}
	if(!timeflag)
	{
		if(upmosti()<3)																	//判断是否失败
		{
			gameOver=true;
			InvalidateRect(hWnd,&pauseRect,FALSE);
			//MessageBox(hWnd,TEXT("GAME OVER!"),
			return;
		}																				//////////////////////////////////////////////////
		
		int temp=0;
		for(i=22;i>=3;)																	//消格
		{
			if(checkbox(i))
			{
				temp++;
				for(k=i;k>=3;k--)
					for(j=0;j<15;j++)
					{
						flag[k][j]=flag[k-1][j];
						RECT tempRect;
						tempRect.left=workRect.left+j*cBlock;
						tempRect.top=workRect.top+(k-3)*cBlock;
						tempRect.right=tempRect.left+cBlock;
						tempRect.bottom=tempRect.top+cBlock;
						InvalidateRect(hWnd,&tempRect,TRUE);
					}
			}
			else
			{
				i--;
			}
		}																					///////////////////////////////////////////////		
		switch(temp)
		{
		case 1:
			iScore+=1;break;
		case 2:
			iScore+=3;break;
		case 3:
			iScore+=5;break;
		case 4:
			iScore+=8;break;
		}
		temp=iLevel;
		iLevel=iScore/100+1;
		if(iLevel==temp+1)
		{
			m_time-=50;
			InvalidateRect(hWnd,&levelRect,TRUE);
		}
		InvalidateRect(hWnd,&scoreRect,TRUE);
		//InvalidateRect(hWnd,&rect,TRUE);
		UpdateBlock(hWnd);
		if(flagTimer)
			SetTimer(hWnd,1,15,NULL);
		else
			SetTimer(hWnd,1,m_time,NULL);
		timeflag=true;
		return;
	}
	int left=40,top=40,right=0,bottom=0;
	for(i=3;i>=0;i--)
	{		
		flag[m_block[i].i][m_block[i].j]=false;
		
		RECT tempRect;
		int x=m_block[i].j,y=m_block[i].i-3;
		tempRect.left=workRect.left+x*cBlock;
		tempRect.top=workRect.top+y*cBlock;
		tempRect.right=tempRect.left+cBlock;
		tempRect.bottom=tempRect.top+cBlock;
		InvalidateRect(hWnd,&tempRect,TRUE);

	/*	left=( (m_block[i].j<left)?m_block[i].j:left );
		top=( (m_block[i].i<top)?m_block[i].i:top );
		right=( (m_block[i].j>right)?m_block[i].j:right );
		bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );*/
		m_block[i].i++;
	}
	for(i=3;i>=0;i--)
	{
	/*	left=( (m_block[i].j<left)?m_block[i].j:left );
		top=( (m_block[i].i<top)?m_block[i].i:top );
		right=( (m_block[i].j>right)?m_block[i].j:right );
		bottom=( (m_block[i].i>bottom)?m_block[i].i:bottom );*/

		flag[m_block[i].i][m_block[i].j]=true;

		RECT tempRect;
		int x=m_block[i].j,y=m_block[i].i-3;
		tempRect.left=workRect.left+x*cBlock;
		tempRect.top=workRect.top+y*cBlock;
		tempRect.right=tempRect.left+cBlock;
		tempRect.bottom=tempRect.top+cBlock;
		InvalidateRect(hWnd,&tempRect,TRUE);
	}
	/*RECT valRect;
	valRect.left=workRect.left+left*cBlock;
	valRect.top=workRect.top+(top-3)*cBlock;
	valRect.right=workRect.left+(right+1)*cBlock;
	valRect.bottom=workRect.top+(bottom-2)*cBlock;*/
//	InvalidateRect(hWnd,&valRect,TRUE);
}

int Maxi()
{
	int i,Max=0;
	for(i=1;i<4;i++)
	{
		if(m_block[i].i>m_block[Max].i)
			Max=i;
	}
	return Max;
}

int rightmostj()
{
	int i,j=m_block[0].j;
	for(i=1;i<4;i++)
	{
		if(m_block[i].j>j)
			j=m_block[i].j;
	}
	return j;
}

int leftmostj()
{
	int j=m_block[0].j,i;
	for(i=1;i<4;i++)
	{
		if(m_block[i].j<j)
		{
			j=m_block[i].j;		
		}
	}
	return j;
}

bool checkbox(int i)
{
	int j;
	for(j=0;j<15;j++)
	{
		if(flag[i][j]==false)
			return false;
	}
	return true;
}

int upmosti()
{
	int i,Max=m_block[0].i;
	for(i=1;i<4;i++)
	{
		if(m_block[i].i<Max)
			Max=m_block[i].i;
	}
	return Max;
}

bool checkabledown()
{
	int i;
	for(i=0;i<4;i++)
	{
		if(!isincluded(m_block[i].i+1,m_block[i].j)&&flag[m_block[i].i+1][m_block[i].j])
			return false;
	}
	return true;
}

bool isincluded(int i,int j)
{
	int k;
	for(k=0;k<4;k++)
	{
		if(m_block[k].i==i&&m_block[k].j==j)
			return true;
	}
	return false;
}

bool checkableleft()
{
	int i;
	for(i=0;i<4;i++)
	{
		if(!isincluded(m_block[i].i,m_block[i].j-1)&&flag[m_block[i].i][m_block[i].j-1])
			return false;
	}
	return true;
}

bool checkableright()
{
	int i;
	for(i=0;i<4;i++)
	{
		if(!isincluded(m_block[i].i,m_block[i].j+1)&&flag[m_block[i].i][m_block[i].j+1])
			return false;
	}
	return true;
}

bool checktempa()
{
	int i;
	for(i=0;i<4;i++)
	{
		if( (tempa[i].i<3||tempa[i].i>22||tempa[i].j<0||tempa[i].j>14)
			||!isincluded(tempa[i].i,tempa[i].j)&&flag[tempa[i].i][tempa[i].j] )
			return false;
	}
	return true;
}

void dd()
{
	int i;
	for(i=0;i<4;i++)
	{
		m_block[i].j-=3;
	}
}

void UpdateBlock(HWND hWnd)
{
	srand(time(NULL));
	m_n=m_nAfter;
	m_nAfter=rand()%19;
	//m_nAfter=2;
	GetNext(hWnd);
	//	m_n=15;
	int i;
	switch(m_n)
	{
	case 0:
		m_block[0].i=0;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=3;m_block[3].j=10;
		dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 1:
		m_block[0].i=2;m_block[0].j=8;
		m_block[1].i=2;m_block[1].j=9;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=2;m_block[3].j=11;
		dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 2:
		m_block[0].i=1;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=11;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=2;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 3:
		m_block[0].i=0;m_block[0].j=11;
		m_block[1].i=1;m_block[1].j=11;
		m_block[2].i=1;m_block[2].j=10;
		m_block[3].i=2;m_block[3].j=10;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 4:
		m_block[0].i=1;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=11;
		m_block[2].i=2;m_block[2].j=11;
		m_block[3].i=2;m_block[3].j=12;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 5:
		m_block[0].i=1;m_block[0].j=10;
		m_block[1].i=2;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=11;
		m_block[3].i=3;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 6:
		m_block[0].i=1;m_block[0].j=11;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=2;m_block[3].j=9;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 7:
		m_block[0].i=1;m_block[0].j=10;
		m_block[1].i=2;m_block[1].j=9;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=2;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 8:
		m_block[0].i=0;m_block[0].j=11;
		m_block[1].i=1;m_block[1].j=11;
		m_block[2].i=2;m_block[2].j=11;
		m_block[3].i=1;m_block[3].j=10;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 9:
		m_block[0].i=1;m_block[0].j=9;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=1;m_block[2].j=11;
		m_block[3].i=2;m_block[3].j=10;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 10:
		m_block[0].i=0;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=1;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 11:
		m_block[0].i=0;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=0;m_block[3].j=9;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 12:
		m_block[0].i=1;m_block[0].j=9;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=1;m_block[2].j=11;
		m_block[3].i=2;m_block[3].j=9;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 13:
		m_block[0].i=0;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=2;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 14:
		m_block[0].i=2;m_block[0].j=9;
		m_block[1].i=2;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=11;
		m_block[3].i=1;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 15:
		m_block[0].i=0;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=0;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 16:
		m_block[0].i=2;m_block[0].j=9;
		m_block[1].i=2;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=11;
		m_block[3].i=1;m_block[3].j=9;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 17:
		m_block[0].i=0;m_block[0].j=10;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=2;m_block[2].j=10;
		m_block[3].i=2;m_block[3].j=9;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	case 18:
		m_block[0].i=1;m_block[0].j=9;
		m_block[1].i=1;m_block[1].j=10;
		m_block[2].i=1;m_block[2].j=11;
		m_block[3].i=2;m_block[3].j=11;dd();
		for(i=0;i<4;i++)
		{
			flag[m_block[i].i][m_block[i].j]=true;
		}
		break;
	}
}

void GetNext(HWND hWnd)
{
	int i,j,k;
	switch(m_nAfter)
	{
	case 0:
		m_blockAfter[0].i=0;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=3;m_blockAfter[3].j=10;
		break;
	case 1:
		m_blockAfter[0].i=2;m_blockAfter[0].j=8;
		m_blockAfter[1].i=2;m_blockAfter[1].j=9;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=2;m_blockAfter[3].j=11;
		break;
	case 2:
		m_blockAfter[0].i=1;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=11;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=2;m_blockAfter[3].j=11;
		break;
	case 3:
		m_blockAfter[0].i=0;m_blockAfter[0].j=11;
		m_blockAfter[1].i=1;m_blockAfter[1].j=11;
		m_blockAfter[2].i=1;m_blockAfter[2].j=10;
		m_blockAfter[3].i=2;m_blockAfter[3].j=10;
		break;
	case 4:
		m_blockAfter[0].i=1;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=11;
		m_blockAfter[2].i=2;m_blockAfter[2].j=11;
		m_blockAfter[3].i=2;m_blockAfter[3].j=12;
		break;
	case 5:
		m_blockAfter[0].i=1;m_blockAfter[0].j=10;
		m_blockAfter[1].i=2;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=11;
		m_blockAfter[3].i=3;m_blockAfter[3].j=11;
		break;
	case 6:
		m_blockAfter[0].i=1;m_blockAfter[0].j=11;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=2;m_blockAfter[3].j=9;
		break;
	case 7:
		m_blockAfter[0].i=1;m_blockAfter[0].j=10;
		m_blockAfter[1].i=2;m_blockAfter[1].j=9;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=2;m_blockAfter[3].j=11;
		break;
	case 8:
		m_blockAfter[0].i=0;m_blockAfter[0].j=11;
		m_blockAfter[1].i=1;m_blockAfter[1].j=11;
		m_blockAfter[2].i=2;m_blockAfter[2].j=11;
		m_blockAfter[3].i=1;m_blockAfter[3].j=10;
		break;
	case 9:
		m_blockAfter[0].i=1;m_blockAfter[0].j=9;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=1;m_blockAfter[2].j=11;
		m_blockAfter[3].i=2;m_blockAfter[3].j=10;
		break;
	case 10:
		m_blockAfter[0].i=0;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=1;m_blockAfter[3].j=11;
		break;
	case 11:
		m_blockAfter[0].i=0;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=0;m_blockAfter[3].j=9;
		break;
	case 12:
		m_blockAfter[0].i=1;m_blockAfter[0].j=9;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=1;m_blockAfter[2].j=11;
		m_blockAfter[3].i=2;m_blockAfter[3].j=9;
		break;
	case 13:
		m_blockAfter[0].i=0;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=2;m_blockAfter[3].j=11;
		break;
	case 14:
		m_blockAfter[0].i=2;m_blockAfter[0].j=9;
		m_blockAfter[1].i=2;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=11;
		m_blockAfter[3].i=1;m_blockAfter[3].j=11;
		break;
	case 15:
		m_blockAfter[0].i=0;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=0;m_blockAfter[3].j=11;
		break;
	case 16:
		m_blockAfter[0].i=2;m_blockAfter[0].j=9;
		m_blockAfter[1].i=2;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=11;
		m_blockAfter[3].i=1;m_blockAfter[3].j=9;
		break;
	case 17:
		m_blockAfter[0].i=0;m_blockAfter[0].j=10;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=2;m_blockAfter[2].j=10;
		m_blockAfter[3].i=2;m_blockAfter[3].j=9;
		break;
	case 18:
		m_blockAfter[0].i=1;m_blockAfter[0].j=9;
		m_blockAfter[1].i=1;m_blockAfter[1].j=10;
		m_blockAfter[2].i=1;m_blockAfter[2].j=11;
		m_blockAfter[3].i=2;m_blockAfter[3].j=11;
		break;
	}
	InvalidateRect(hWnd,&showRect,TRUE);
}