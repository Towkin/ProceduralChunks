#include "ImageLayerChunk.h"



ImageLayerChunk::ImageLayerChunk() :
	Chunk(),
	ImageChunk(),
	LayerChunk()
{}


ImageLayerChunk::~ImageLayerChunk() {}

void ImageLayerChunk::Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) {
	ImageChunk::Draw(aRenderer, aRenderRect);
	LayerChunk::Draw(aRenderer, aRenderRect);
}
