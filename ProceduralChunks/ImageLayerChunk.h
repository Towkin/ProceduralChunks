#pragma once
#include "ImageChunk.h"
#include "LayerChunk.h"

class ImageLayerChunk : public ImageChunk, public LayerChunk {
public:
	ImageLayerChunk();
	virtual ~ImageLayerChunk();

	virtual void Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) override;
	virtual bool IsImage() const { return true; }
};

