#ifndef __TETRISDEF_H__
#define __TETRISDEF_H__

namespace tetris
{
	enum ETetrisDef
	{
		MaxTetrisRows = 21,
		MaxTetrisCols = 14,
		MaxVertexCount = 10,
		MaxInitialEntities = 100,
		GameFps = 60,
	};

#define TetrisAssert(x) if (!(x)) { __asm {int 3}; }
// #define TetrisAssert(x)
#define eps 0.00001
}

#endif // __TETRISDEF_H__