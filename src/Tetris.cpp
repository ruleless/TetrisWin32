#include "Tetris.h"
#include "Renderable.h"

namespace tetris
{
	Tetris::Tetris()
		:mGameState(GameState_Unkown)
		,mTerrainArea(Vector2(0.05, 0.05), Vector2(0.6, 0.95))
	{
		memset(mTerrain, false, sizeof(mTerrain));
		memset(mInitialEntities, 0, sizeof(mInitialEntities));
		mInitialEntityCount = 0;
		mCurEntity = NULL;
		mNextEntity = NULL;
		mElapse = 0;
		mFreq = 0.1;
	}

	Tetris::~Tetris()
	{
	}

	bool Tetris::initialise()
	{
		if (mGameState != GameState_Unkown)
		{
			return true;
		}
		mGameState = GameState_Inited;
		mInitialEntities[mInitialEntityCount++] = Entity_1::ObjPool().createObject();
		mInitialEntities[mInitialEntityCount++] = Entity_2::ObjPool().createObject();
		mInitialEntities[mInitialEntityCount++] = Entity_3::ObjPool().createObject();
		mInitialEntities[mInitialEntityCount++] = Entity_4::ObjPool().createObject();
		mInitialEntities[mInitialEntityCount++] = Entity_5::ObjPool().createObject();
		mInitialEntities[mInitialEntityCount++] = Entity_6::ObjPool().createObject();
		mInitialEntities[mInitialEntityCount++] = Entity_7::ObjPool().createObject();
		mInitialEntities[mInitialEntityCount++] = Entity_8::ObjPool().createObject();
		
		return true;
	}

	void Tetris::finalise()
	{
		for (int i = 0; i < mInitialEntityCount; ++i)
		{
			if (mInitialEntities[i])
			{
				mInitialEntities[i]->release();
				mInitialEntities[i] = NULL;
			}
		}
		mInitialEntityCount = 0;
		mGameState = GameState_Unkown;
	}

	bool Tetris::start()
	{
		_setState(GameState_Game);
		return true;
	}

	bool Tetris::pause()
	{
		_setState(GameState_Pause);
		return true;
	}

	bool Tetris::_setState(EGameState gs)
	{
		switch (gs)
		{
		case GameState_Game:
			{
				switch (mGameState)
				{
				case GameState_Inited:
				case GameState_Over:
					{
						memset(mTerrain, 0, sizeof(mTerrain));

						mGameState = gs;
						if (mCurEntity)
							mCurEntity->release();
						if (mNextEntity)
							mNextEntity->release();
						mCurEntity = _generateEntity();
						mNextEntity = _generateEntity();
						srand(time(NULL));
					}
					break;
				case GameState_Pause:
					mGameState =gs;
					break;
				}
			}
			break;
		case GameState_Pause:
			{
				switch (mGameState)
				{
				case GameState_Game:
					mGameState = gs;
					break;
				}
			}
			break;
		case GameState_Over:
			{
				switch (mGameState)
				{
				case GameState_Game:
					mGameState = gs;
					break;
				}
			}
			break;
		default:
			break;
		}
		return true;
	}

	Entity* Tetris::_generateEntity()
	{
		Entity *pInitial = mInitialEntities[rand()%mInitialEntityCount];
		Entity *pNewEntity = pInitial->clone();
		pNewEntity->translate(Vector2((MaxTetrisCols>>1)-1, 0));

		int rotTimes = rand()%4;
		while (rotTimes--)
		{
			pNewEntity->rotate(getMatForRot90());
		}
		return pNewEntity;
	}

	void Tetris::injectKeyDown(char key)
	{
		switch (mGameState)
		{
		case GameState_Game:
			{
				if (mCurEntity)
				{
					switch (key)
					{
					case 'A':
						mCurEntity->translate(Vector2(-1, 0));
						break;
					case 'D':
						mCurEntity->translate(Vector2(1, 0));
						break;
					case 'J':
						mCurEntity->rotate(getMatForRot90());
						break;
					case 'S':
						mCurEntity->translate(Vector2(0, 1));
						break;
					case 'W':
						pause();
						break;
					default:
						break;
					}
				}
			}
			break;
		case GameState_Pause:
			if ('W' == key)
			{
				start();
			}
			break;
		default:
			break;
		}
	}

	void Tetris::injectKeyUp(char key)
	{
	}

	void Tetris::update(float delta)
	{
		switch (mGameState)
		{
		case GameState_Game:
			{
				mElapse += delta;
				if (mElapse >= mFreq)
				{
					mElapse = 0;
					tickOnce();
				}
			}
			break;
		case GameState_Over:
			{
				mElapse += delta;
				if (mElapse >= 2)
				{
					start();
					mElapse = 0;
				}
			}
		}
	}

	void Tetris::tickOnce()
	{
		if (mCurEntity)
		{
			if (Entity::State_Dead == mCurEntity->state())
			{
				if (mCurEntity->translate(Vector2(0, 1)))
				{
					mCurEntity->state(Entity::State_Alive);
					return;
				}
				Vector2 verts[MaxVertexCount];
				int vertscount = MaxVertexCount;
				if (mCurEntity->getAllVertex(verts, vertscount) > 0)
				{
					for (int k = 0; k < vertscount; ++k)
					{
						int i = verts[k].x;
						int j = verts[k].y;
						if (i >= 0 && i < MaxTetrisCols && j >= 0 && j < MaxTetrisRows)
						{
							mTerrain[i][j] = true;
						}
					}
				}
				mCurEntity->release();
				mCurEntity = NULL;
			}
			else
			{
				if (!mCurEntity->translate(Vector2(0, 1)))
				{
					mCurEntity->state(Entity::State_Dead);
				}
			}
		}
		else
		{
			if (mNextEntity->collision())
			{
				mNextEntity->release();
				mNextEntity = NULL;
				_setState(GameState_Over);
				return;
			}
			mCurEntity = mNextEntity;
			mNextEntity = _generateEntity();
		}

		for (int j = MaxTetrisRows-1; j >= 0;)
		{
			bool done = true;
			for (int i = 0; i < MaxTetrisCols; ++i)
			{
				if (!mTerrain[i][j])
				{
					done = false;
					break;
				}
			}
			if (done)
			{
				for (int k = j; k >= 0; --k)
				{
					for (int i = 0; i < MaxTetrisCols; ++i)
					{
						mTerrain[i][k] = k>0 ? mTerrain[i][k-1] : false;
					}
				}
			}
			else
			{
				--j;
			}
		}
	}

	bool Tetris::collision(int i, int j)
	{
		if (i >= 0 && i < MaxTetrisCols && j < MaxTetrisRows)
		{
			if (j >= 0)
			{
				return mTerrain[i][j];
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	void Tetris::render(RenderSystem *pRenderSystem)
	{
		RenderableRect *r = RenderableRect::ObjPool().createObject();
		Vector2x2 screenArea = pRenderSystem->getRenderArea();
		r->setShape(screenArea.v1, screenArea.v2);
		r->setRGB(SRgb(60, 50, 50));
		pRenderSystem->addRenderable(r);

		// Draw Terrain Area
		RenderableRect *terrainArea = RenderableRect::ObjPool().createObject();
		terrainArea->setShape(_toScreen(screenArea, mTerrainArea));
		terrainArea->setRGB(SRgb(165, 188, 188));
		pRenderSystem->addRenderable(terrainArea);

		// Draw Lines
		for (int j = 0; j < MaxTetrisRows; ++j)
		{
			RenderableLine *line = RenderableLine::ObjPool().createObject();
			line->setShape(_getHorzLine(screenArea, j));
			line->setRGB(SRgb(120, 120, 120));
			pRenderSystem->addRenderable(line);
		}
		for (int i = 0; i < MaxTetrisCols; ++i)
		{
			RenderableLine *line = RenderableLine::ObjPool().createObject();
			line->setShape(_getVertLine(screenArea, i));
			line->setRGB(SRgb(120, 120, 120));
			pRenderSystem->addRenderable(line);
		}

		// Draw Terrain
		for (int i = 0; i < MaxTetrisCols; ++i)
		{
			for (int j = 0; j < MaxTetrisRows; ++j)
			{
				if (mTerrain[i][j])
				{
					RenderableRect *block = RenderableRect::ObjPool().createObject();
					block->setShape(_getBlockArea(screenArea, i, j));
					block->setRGB(SRgb(100, 160, 170));
					pRenderSystem->addRenderable(block);
				}
			}
		}

		// Block Entity
		if (mCurEntity)
		{
			Vector2 verts[MaxVertexCount];
			int vertscount = MaxVertexCount;
			if (mCurEntity->getAllVertex(verts, vertscount) > 0)
			{
				for (int k = 0; k < vertscount; ++k)
				{
					int i = verts[k].x;
					int j = verts[k].y;
					if (i >= 0 && i < MaxTetrisCols && j >= 0 && j < MaxTetrisRows)
					{
						RenderableRect *block = RenderableRect::ObjPool().createObject();
						block->setShape(_getBlockArea(screenArea, i, j));
						block->setRGB(SRgb(100, 160, 170));
						pRenderSystem->addRenderable(block);
					}
				}
			}
		}
	}

	Vector2x2 Tetris::_getHorzLine(const Vector2x2 &screenArea, int row) const
	{
		Vector2x2 l;
		l.v1 = mTerrainArea.v1;
		l.v1.y += mTerrainArea.getHeight()*row*1.0/MaxTetrisRows;
		l.v2 = mTerrainArea.v2;
		l.v2.y = l.v1.y;
		return _toScreen(screenArea, l);
	}

	Vector2x2 Tetris::_getVertLine(const Vector2x2 &screenArea, int col) const
	{
		Vector2x2 l;
		l.v1 = mTerrainArea.v1;
		l.v1.x += mTerrainArea.getWidth()*col*1.0/MaxTetrisCols;
		l.v2 = mTerrainArea.v2;
		l.v2.x = l.v1.x;
		return _toScreen(screenArea, l);
	}

	Vector2x2 Tetris::_getBlockArea(const Vector2x2 &screenArea, int i, int j) const
	{
		Vector2x2 b;
		b.v1.x = mTerrainArea.getWidth()*i*1.0/MaxTetrisCols;
		b.v2.x = b.v1.x+mTerrainArea.getWidth()*1.0/MaxTetrisCols;
		b.v1.y = mTerrainArea.getHeight()*j*1.0/MaxTetrisRows;
		b.v2.y = b.v1.y+mTerrainArea.getHeight()*1.0/MaxTetrisRows;

		b.v1 += mTerrainArea.v1;
		b.v2 += mTerrainArea.v1;
		return _toScreen(screenArea, b);
	}

	Vector2x2 Tetris::_toScreen(const Vector2x2 &screenArea, const Vector2x2 &s) const
	{
		Vector2x2 r;
		r.v1.x = s.v1.x*screenArea.getWidth();
		r.v1.y = s.v1.y*screenArea.getHeight();
		r.v2.x = s.v2.x*screenArea.getWidth();
		r.v2.y = s.v2.y*screenArea.getHeight();
		return r;
	}
}