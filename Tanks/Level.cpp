#include "Level.h"
#include "Scout.h"
#include "Defender.h"
#include "Raider.h"

Level::Level(PlayerUI* playerUI,  Player* player)
{
	mTimer = Timer::Instance();

	mPlayerUI = playerUI;
	mPlayer = player;

	mLevel = 1;
	mNumberOfEnemies = ceil(mLevel * 1.5f);
	mLevelStarted = false;

	mTileManager = TileManager::Instance();

	mGameOverLabel = new Texture("YOU LOSE", "Fonts/Kenney Pixel Square.ttf", 48, { 124, 94, 22 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;

	mSpawnDelay = 5.0f;
	mSpawnTimer = 0.0f;
	mSpawn = 0;
}

Level::~Level()
{
	mTimer = nullptr;

	mPlayer = nullptr;

	mTileManager->Release();
	mTileManager = nullptr;

	KillEnemies();

	delete mGameOverLabel;
	mGameOverLabel = nullptr;
}

Level::LEVEL_STATES Level::State()
{
	return mCurrentState;
}

void Level::SetCurrentLevel(int level)
{
	mLevel = level;

	if (level % 5)
		mNumberOfEnemies = ceil(mLevel * 1.5f);
	else
		mNumberOfEnemies = mLevel / 5.0f;

	mLevelStarted = false;
	mCurrentState = running;
}

void Level::StartLevel()
{
	mSpawn = rand() % mTileManager->SpawnPos().size();
	mLevelStarted = true;
	mPlayerUI->Level(mLevel);
}

void Level::KillEnemies()
{
	for (int i = 0; i < mEnemy.size(); i++)
	{
		delete mEnemy[i];
		mEnemy[i] = nullptr;
	}

	mEnemy.clear();
}

void Level::HandleEnemies()
{
	for (int i = 0; i < mEnemy.size(); i++)
	{
		mEnemy[i]->Update();

		if (mEnemy[i]->Dead())
		{
			mPlayer->AddScore(mEnemy[i]->Value());
			mPlayerUI->Score(mPlayer->Score());

			delete mEnemy[i];
			mEnemy[i] = nullptr;
			mEnemy.erase(mEnemy.begin() + i);
		}
	}

	if (mNumberOfEnemies > 0)
	{
		if (mEnemy.size() < 3)
		{
			if (mLevel % 5)
			{
				if ( mLevel > 10 ? !(mLevel % 2) : !(mLevel % 3))
				{
					if (rand() % 4)
						mEnemy.push_back(new Scout(mTileManager->SpawnPos()[mSpawn]));
					else
						mEnemy.push_back(new Raider(mTileManager->SpawnPos()[mSpawn]));
				}
				else
					mEnemy.push_back(new Scout(mTileManager->SpawnPos()[mSpawn]));
			}
			else
				mEnemy.push_back(new Defender(mTileManager->SpawnPos()[mSpawn]));

			mEnemy.back()->Target(mPlayer->GetTank());

			mNumberOfEnemies--;

			if (mSpawn < mTileManager->SpawnPos().size() - 1)
				mSpawn++;
			else
				mSpawn = 0;

			mSpawnTimer = mSpawnDelay;
		}
		else if ((mEnemy.size() < 10 && mSpawnTimer <= 0.0f))
		{
			mSpawn = rand() % mTileManager->SpawnPos().size();

			if (mLevel % 5)
			{
				if (mLevel > 10 ? !(mLevel % 2) : !(mLevel % 3))
				{
					if (rand() % 4)
						mEnemy.push_back(new Scout(mTileManager->SpawnPos()[mSpawn]));
					else
						mEnemy.push_back(new Raider(mTileManager->SpawnPos()[mSpawn]));
				}
				else
					mEnemy.push_back(new Scout(mTileManager->SpawnPos()[mSpawn]));
			}
			else
				mEnemy.push_back(new Defender(mTileManager->SpawnPos()[mSpawn]));

			mEnemy.back()->Target(mPlayer->GetTank());

			mNumberOfEnemies--;

			mSpawnTimer = mSpawnDelay;
		}
		else
			mSpawnTimer -= mTimer->DeltaTime();
	}
}

void Level::Update()
{
	mTileManager->Update();

	if (mLevelStarted)
		HandleEnemies();

	if (mPlayer->Dead())
	{
		mPlayer->Active(false);

		if (!mPlayer->GetTank()->IsAnimating())
		{
			if (mGameOverTimer == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();

			if (mGameOverTimer >= mGameOverDelay)
			{
				KillEnemies();
				mCurrentState = gameover;
				mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
			}
		}
	}
	else if (!mEnemy.size() && !mNumberOfEnemies)
	{
		mCurrentState = levelover;

		if (!(mLevel % 5))
			mPlayer->Heal();
	}

	mPlayerUI->Health(mPlayer->Health());

	if (mGameOverTimer >= mGameOverLabelOnScreen)
		mGameOverLabel->Translate(VEC2_UP * 35.0f * mTimer->DeltaTime());
}

void Level::Render()
{
	mTileManager->Render();

	mPlayer->Render();

	if (mLevelStarted)
	{
		for (const auto &enemy : mEnemy)
			enemy->Render();
	}

	if (mGameOverTimer >= mGameOverLabelOnScreen)
		mGameOverLabel->Render();
}