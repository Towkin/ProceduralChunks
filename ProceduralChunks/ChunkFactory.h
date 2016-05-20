#pragma once

class Chunk;
class ChunkFactory
{
private:
	
	

	static float sHeightBaseFrequency;
	static unsigned int sHeightOctaves;
	static unsigned int sHeightSeed;
	static float sHeightLacunarity;
	static float sHeightPersistance;

	static float sDryBaseFrequency;
	static unsigned int sDryOctaves;
	static unsigned int sDrySeed;
	static float sDryLacunarity;
	static float sDryPersistance;



	static float sHeightMin;
	static float sHeightMax;

	static float sDryMin;
	static float sDryMax;
	

	ChunkFactory();
	~ChunkFactory();
public:
	static Chunk* GenerateChunk(float aX, float aY, float aSize, int aResolution, unsigned int aLayer);
};

