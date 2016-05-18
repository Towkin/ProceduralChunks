#pragma once

class Chunk;
class ChunkFactory
{
private:
	static unsigned int sHeightSeed;
	static unsigned int sDrySeed;
	ChunkFactory();
	~ChunkFactory();
public:
	static Chunk* GenerateChunk(float aX, float aY, float aSize, int aResolution, unsigned int aLayer);
};

