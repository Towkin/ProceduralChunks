#include "ChunkManager.h"
#include "ChunkFactory.h"


ChunkManager::ChunkManager():
	mChunkResolution(512),
	mChunkSize(1000.f),
	mChunks(ChunkGrid())
{}


ChunkManager::~ChunkManager()
{}

Chunk* ChunkManager::GetChunk(size_t aX, size_t aY) {
	if (aX >= mChunks.size()) {
		mChunks.resize(aX + 1);
	}
	if (aY >= mChunks[aX].size()) {
		mChunks[aX].resize(aY + 1);
	}
	
	float OffsetX = 25000;
	float OffsetY = 25000;

	if (mChunks[aX][aY] == nullptr) {
		mChunks[aX][aY] = ChunkFactory::GenerateChunk(aX * GetChunkSize() + OffsetX, aY * GetChunkSize() + OffsetY, GetChunkSize(), GetChunkResolution(), 0);
	}
	return mChunks[aX][aY];
}
