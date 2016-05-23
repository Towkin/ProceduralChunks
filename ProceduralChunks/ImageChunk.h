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
	virtual void Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect);

	ImageChunk();
	~ImageChunk();

};

