#include "LayerChunk.h"
#include "ChunkFactory.h"

bool LayerChunk::sUglyHasLoaded = false;

LayerChunk::LayerChunk() {}


LayerChunk::~LayerChunk() {
	for (Chunk* SubChunk : mChunks) {
		delete SubChunk;
	}
}

void LayerChunk::SetChunksResolution(size_t aNewResolution) {
	mChunksResolution = aNewResolution;
	mChunks.resize(aNewResolution * aNewResolution);
}

void LayerChunk::RemoveChild(Chunk* aChild) {
	for (size_t i = 0; i < GetChunksResolution() * GetChunksResolution(); i++) {
		if (mChunks[i] == aChild) {
			mChunks[i] = nullptr;
			break;
		}
	}
}

bool LayerChunk::ValidChunk(size_t aX, size_t aY) const {
	return (aX < GetChunksResolution() && aY < GetChunksResolution());
}

float Clamp(float value, float min, float max) {
	return std::fminf(max, std::fmaxf(min, value));
}
void LayerChunk::Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) {
	
	ImageChunk::Draw(aRenderer, aRenderRect);
	
	if ((aRenderer->getSize().x / GetResolution()) * (GetSize() / aRenderRect.width) > 1.5f ||
		(aRenderer->getSize().y / GetResolution()) * (GetSize() / aRenderRect.height) > 1.5f) {

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
				Chunk* DrawChunk = GetChunk(x, y);
				if (DrawChunk) {
					DrawChunk->Draw(aRenderer, aRenderRect);
				}
			}
		}
	}
}

Chunk* LayerChunk::GetChunk(size_t aX, size_t aY) {
	Chunk* ReturnChunk = nullptr;
	if (ValidChunk(aX, aY)) {
		if (mChunks[aX + GetChunksResolution() * aY] == nullptr && !sUglyHasLoaded) {
			mChunks[aX + GetChunksResolution() * aY] = ChunkFactory::GenerateChunk(GetX() + aX * GetChildSize(), GetY() + aY * GetChildSize(), GetChildSize(), GetResolution(), GetLayer() - 1);
			mChunks[aX + GetChunksResolution() * aY]->SetParent(this);
			sUglyHasLoaded = true;
		}
		ReturnChunk = mChunks[aX + GetChunksResolution() * aY];
	}
	
	return ReturnChunk;
}
