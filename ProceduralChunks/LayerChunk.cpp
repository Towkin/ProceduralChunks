#include "LayerChunk.h"
#include "ChunkFactory.h"


LayerChunk::LayerChunk() {}


LayerChunk::~LayerChunk() {}

void LayerChunk::SetChunksResolution(size_t aNewResolution) {
	mChunksResolution = aNewResolution;
	mChunks.resize(aNewResolution * aNewResolution);
}

bool LayerChunk::ValidChunk(size_t aX, size_t aY) const {
	return (aX < GetChunksResolution() && aY < GetChunksResolution());
}

float Clamp(float value, float min, float max) {
	return std::fminf(max, std::fmaxf(min, value));
}
#include <iostream>
void LayerChunk::Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) {
	if (GetSize() / aRenderRect.width > 1.5f ||
		GetSize() / aRenderRect.height > 1.5f) {

		size_t StartX = Clamp(
			std::floorf((aRenderRect.left - GetX()) / GetChildSize()),
			0, GetChunksResolution()
		);
		size_t StartY = Clamp(
			std::floorf((aRenderRect.top - GetY()) / GetChildSize()),
			0, GetChunksResolution()
		);

		size_t EndX = Clamp(
			std::ceilf((aRenderRect.left + aRenderRect.width - GetX()) / GetChildSize()),
			0, GetChunksResolution()
		);
		size_t EndY = Clamp(
			std::ceilf((aRenderRect.top + aRenderRect.height - GetY()) / GetChildSize()),
			0, GetChunksResolution()
		);

		for (size_t x = StartX; x < EndX; x++) {
			for (size_t y = StartY; y < EndY; y++) {
				GetChunk(x, y)->Draw(aRenderer, aRenderRect);
			}
		}
	} else {
		Chunk::Draw(aRenderer, aRenderRect);
	}
}

Chunk* LayerChunk::GetChunk(size_t aX, size_t aY) {
	Chunk* ReturnChunk;
	if (ValidChunk(aX, aY)) {
		if (mChunks[aX + GetChunksResolution() * aY] == nullptr) {
			mChunks[aX + GetChunksResolution() * aY] = ChunkFactory::GenerateChunk(GetX() + aX * GetChildSize(), GetY() + aY * GetChildSize(), GetChildSize(), GetResolution(), GetLayer() - 1);
		}
		ReturnChunk = mChunks[aX + GetChunksResolution() * aY];
	}
	
	return ReturnChunk;
}
