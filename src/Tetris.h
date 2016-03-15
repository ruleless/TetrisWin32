#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdio.h>
#include "RenderSystem.h"

class Tetris
{
public:
	enum EGameState
	{
		GameState_Unkown,
		GameState_Inited,

		GameState_Game,
		GameState_Pause,
		GameState_Over,
	};

	Tetris();
	virtual ~Tetris();

	bool initialise();
	void finalise();

	bool start();
	bool pause();

	bool _setState(EGameState gs);

	void update(float delta);
	void render(RenderSystem *pRenderSystem);
protected:
	EGameState mGameState;
};

#endif // __TETRIS_H__