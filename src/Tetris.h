#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdio.h>
#include "RenderSystem.h"
#include "TetrisDef.h"
#include "Entity.h"

namespace tetris
{
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

		Entity* _generateEntity();

		void injectKeyDown(char key);
		void injectKeyUp(char key);

		void update(float delta);
		void tickOnce();
		bool collision(int i, int j);

		void render(RenderSystem *pRenderSystem);

		Vector2x2 _getHorzLine(const Vector2x2 &screenArea, int row) const;
		Vector2x2 _getVertLine(const Vector2x2 &screenArea, int col) const;
		Vector2x2 _getBlockArea(const Vector2x2 &screenArea, int i, int j) const;

		Vector2x2 _toScreen(const Vector2x2 &screenArea, const Vector2x2 &s) const;
	protected:
		EGameState mGameState;
		Vector2x2 mTerrainArea;
		bool mTerrain[MaxTetrisCols][MaxTetrisRows];

		Entity *mInitialEntities[MaxInitialEntities];
		int mInitialEntityCount;

		Entity *mCurEntity;
		Entity *mNextEntity;

		float mElapse;
		float mFreq;
	};
}

#endif // __TETRIS_H__