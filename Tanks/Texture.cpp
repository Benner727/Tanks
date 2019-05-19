#include "Texture.h"

Texture::Texture(std::string filename)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mFlash = false;
	mFlashFrames = 0;
}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mWidth;

	mFlash = false;
	mFlashFrames = 0;
}

Texture::Texture(std::string text, std::string fontpath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontpath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mFlash = false;
	mFlashFrames = 0;
}

Texture::~Texture()
{
	mTex = nullptr;
	mGraphics = nullptr;
}

Vector2 Texture::ScaledDimensions()
{
	Vector2 scaledDimensions = Scale();
	scaledDimensions.x *= mWidth;
	scaledDimensions.y *= mHeight;

	return scaledDimensions;
}

void Texture::Color(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTex, red, green, blue);
}

void Texture::Flash()
{
	mFlash = true;
}

void Texture::Render()
{
	Vector2 pos = Pos(world);
	Vector2 scale = Scale(world);

	mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight *  scale.y * 0.5f);

	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	if (mFlash)
	{
		Color(0, 0, 0);
		mFlashFrames++;
	}
	else
		Color(255, 255, 255);

	mGraphics->DrawTexture(mTex, (mClipped)? &mClipRect : nullptr, &mRenderRect, Rotation(world));

	if (mFlash && mFlashFrames >= 3)
	{
		Color(255, 255, 255);
		mFlash = false;
		mFlashFrames = 0;
	}
}