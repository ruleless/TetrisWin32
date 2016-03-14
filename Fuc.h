struct Node
{
	int i,j;
};

void InitGame(HWND);
void TimeFun(HWND);

struct Node tempa[4],m_blockAfter[4];
bool checkableright();
bool checkableleft();
bool isincluded(int i,int j);
bool checkabledown();
int m_n,m_nAfter;
int upmosti();
bool checkbox(int i);
bool pressflag;
void UpdateBlock(HWND);
int leftmostj();
int rightmostj();
int Maxi();
bool flagTimer;
bool checktempa();
void GetNext(HWND);
void dd();
struct Node m_block[4];
