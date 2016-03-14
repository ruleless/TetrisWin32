#include "Fuc.h"
#include "StdAfx.h"
#include "Valuable.h"

void InitGame(HWND hWnd)
{
	int i,j;								//初始化网格
	for(i=0;i<20;i++)
	{
		for(j=0;j<15;j++)
		{
			flag[i][j]=false;
			m_grid[i][j].left=workRect.left+j*cBlock;
			m_grid[i][j].top=workRect.top+i*cBlock;
			m_grid[i][j].right=workRect.left+(j+1)*cBlock;
			m_grid[i][j].bottom=workRect.top+(i+1)*cBlock;
		}
	}
	m_time=300;
	SetTimer(hWnd,1,m_time,NULL);				//设置定时器消息
	timeflag=true;
}
