#pragma once
#include "Chunk.h"
class ImageChunk :
	public Chunk {

public:

	const static bool sShouldLerpColors;

private:
	sf::RectangleShape mDrawRectangle;
	sf::Texture mTexture;
	sf::Image mImage;

	static sf::Image sMapColors;
	static sf::Image GetMapColors();

public:
	const sf::Image& GetImage() const { return mImage; }

	virtual void ApplyData();
	static void ApplyArea(ImageChunk* aChunk, size_t aStartX, size_t aStartY, size_t aEndX, size_t aEndY);
	virtual void Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect);

	ImageChunk();
	virtual ~ImageChunk();

};

