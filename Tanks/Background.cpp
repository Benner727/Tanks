#include "Background.h"



Background::Background()
{
	mTimer = Timer::Instance();

	Initialize();
}


Background::~Background()
{
	mTimer = nullptr;

	for (int i = 0; i < mTiles.size(); i++)
	{
		for (int j = 0; j < mTiles[i].size(); j++)
		{
			delete mTiles[i][j];
			mTiles[i][j] = nullptr;
		}
	}

	mTiles.clear();

	for (int i = 0; i < mObjects.size(); i++)
	{
		delete mObjects[i];
		mObjects[i] = nullptr;
	}

	mObjects.clear();

	delete mTank;
	mTank = nullptr;
}

void Background::Initialize()
{
	std::string texture;

	for (int i = 0; i < 14; i++)
	{
		mTiles.push_back({});

		for (int j = 0; j < 16; j++)
		{
			if (rand() % 2)
				texture = "Tiles/tileSand1.png";
			else
				texture = "Tiles/tileSand2.png";

			if (i == 11 && j < 7)
				texture = "Tiles/tileSand_roadEast.png";

			mTiles.back().push_back(new Texture(texture));
			mTiles.back().back()->Parent(this);
			mTiles.back().back()->Pos(Vector2(j * 64 + 32, i * 64 + 32));
		}
	}

	mObjects.push_back(new Texture("Objects/crateWood.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(255, 655));

	mObjects.push_back(new Texture("Objects/crateWood.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(285, 555));

	mObjects.push_back(new Texture("Objects/crateWood.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(305, 655));

	mObjects.push_back(new Texture("Objects/barrelRed_top.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(275, 605));

	mObjects.push_back(new Texture("Objects/oilSpill_large.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(325, 605));

	mObjects.push_back(new Texture("Objects/fenceYellow.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(450, 735));
	mObjects.back()->Rotate(90.0f);

	mObjects.push_back(new Texture("Objects/treeBrown_large.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(125, 650));

	mObjects.push_back(new Texture("Objects/barricadeWood.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(145, 775));

	mObjects.push_back(new Texture("Objects/barricadeWood.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(195, 785));

	mObjects.push_back(new Texture("Objects/barricadeWood.png"));
	mObjects.back()->Parent(this);
	mObjects.back()->Pos(Vector2(225, 775));

	mTank = new Texture("Tiles/tank_red.png");
	mTank->Parent(this);
	mTank->Pos(Vector2(-50.0f, 735.0f));
	mTank->Rotate(-90.0f);
}

void Background::HandleTank()
{
	if (mTank->Pos(world).x <= 400.0f)
	{
		mTank->Translate(VEC2_RIGHT * 50.0f * mTimer->DeltaTime());
	}
}

void Background::Restart()
{
	mTank->Pos(Vector2(-50.0f, 735.0f));
}

void Background::Update()
{
	HandleTank();
}

void Background::Render()
{
	for (int i = 0; i < mTiles.size(); i++)
	{
		for (int j = 0; j < mTiles[i].size(); j++)
		{
			mTiles[i][j]->Render();
		}
	}

	for (const auto &object : mObjects)
		object->Render();

	mTank->Render();
}