#pragma once

#include <vector>

class Chunk;
class ChunkManager
{
private:
	typedef std::vector<std::vector<Chunk*>> ChunkGrid;
	ChunkGrid mChunks;
	size_t mChunkResolution;
	float mChunkSize;
public:
	ChunkManager();
	~ChunkManager();

	Chunk* GetChunk(size_t aX, size_t aY);
	
	float GetChunkSize() const { return mChunkSize; }
	void SetChunkSize(float aNewSize) { mChunkSize = aNewSize; }
	
	size_t GetChunkResolution() const { return mChunkResolution; }
	void SetChunkResolution(size_t aNewResolution) { mChunkResolution = aNewResolution; }
};

