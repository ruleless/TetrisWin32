#include <stdio.h>

void GetNext()
{
	int i,j,k;
	switch(m_nAfter)
	{
	case 0:
		m_blockAfterAfter[0].i=0;m_blockAfterAfter[0].j=10;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=10;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=10;
		m_blockAfterAfter[3].i=3;m_blockAfterAfter[3].j=10;
		break;
	case 1:
		m_blockAfterAfter[0].i=2;m_blockAfterAfter[0].j=8;
		m_blockAfterAfter[1].i=2;m_blockAfterAfter[1].j=9;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=10;
		m_blockAfterAfter[3].i=2;m_blockAfterAfter[3].j=11;
		break;
	case 2:
		m_blockAfterAfter[0].i=1;m_blockAfterAfter[0].j=10;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=11;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=10;
		m_blockAfterAfter[3].i=2;m_blockAfterAfter[3].j=11;
		break;
	case 3:
		m_blockAfterAfter[0].i=0;m_blockAfterAfter[0].j=11;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=11;
		m_blockAfterAfter[2].i=1;m_blockAfterAfter[2].j=10;
		m_blockAfterAfter[3].i=2;m_blockAfterAfter[3].j=10;
		break;
	case 4:
		m_blockAfterAfter[0].i=1;m_blockAfterAfter[0].j=10;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=11;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=11;
		m_blockAfterAfter[3].i=2;m_blockAfterAfter[3].j=12;
		break;
	case 5:
		m_blockAfterAfter[0].i=1;m_blockAfterAfter[0].j=10;
		m_blockAfterAfter[1].i=2;m_blockAfterAfter[1].j=10;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=11;
		m_blockAfterAfter[3].i=3;m_blockAfterAfter[3].j=11;
		break;
	case 6:
		m_blockAfterAfter[0].i=1;m_blockAfterAfter[0].j=11;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=10;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=10;
		m_blockAfterAfter[3].i=2;m_blockAfterAfter[3].j=9;
		break;
	case 7:
		m_blockAfterAfter[0].i=1;m_blockAfterAfter[0].j=10;
		m_blockAfterAfter[1].i=2;m_blockAfterAfter[1].j=9;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=10;
		m_blockAfterAfter[3].i=2;m_blockAfterAfter[3].j=11;
		break;
	case 8:
		m_blockAfterAfter[0].i=0;m_blockAfterAfter[0].j=11;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=11;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=11;
		m_blockAfterAfter[3].i=1;m_blockAfterAfter[3].j=10;
		break;
	case 9:
		m_blockAfterAfter[0].i=1;m_blockAfterAfter[0].j=9;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=10;
		m_blockAfterAfter[2].i=1;m_blockAfterAfter[2].j=11;
		m_blockAfterAfter[3].i=2;m_blockAfterAfter[3].j=10;
		break;
	case 10:
		m_blockAfterAfter[0].i=0;m_blockAfterAfter[0].j=10;
		m_blockAfterAfter[1].i=1;m_blockAfterAfter[1].j=10;
		m_blockAfterAfter[2].i=2;m_blockAfterAfter[2].j=10;
		m_blockAfterAfter[3].i=1;m_blockAfterAfter[3].j=11;
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
}