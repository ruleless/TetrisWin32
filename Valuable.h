#define MAX_LOADSTRING 100

bool flag[30][20],timeflag,flagPause,gameOver;
RECT m_grid[30][20];
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
RECT workRect,rect,showRect,levelRect,scoreRect,pauseRect;
int cBlock,m_time,iLevel,iScore;

