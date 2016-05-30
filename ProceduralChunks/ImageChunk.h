#pragma once
#include "Chunk.h"
class ImageChunk :
	public virtual Chunk {

private:
	sf::RectangleShape mDrawRectangle;
	sf::Texture mTexture;
	sf::Image mImage;

	static sf::Image sMapColors;
	static sf::Image GetMapColors();

	virtual sf::Color GetColorFromMap(float x, float y) const;

	static void ApplyArea(ImageChunk* aChunk, size_t aStartX, size_t aStartY, size_t aEndX, size_t aEndY);
	virtual sf::Color GetColor(size_t aX, size_t aY);
public:
	const sf::Image& GetImage() const { return mImage; }

	virtual void ApplyData();
	virtual void Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect);

	ImageChunk();
	virtual ~ImageChunk();

};

