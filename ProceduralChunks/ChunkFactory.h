#pragma once

class Chunk;
class ChunkFactory
{
private:
	static const float sHeightBaseFrequency;
	static const unsigned int sHeightOctaves;
	static const unsigned int sHeightSeed;
	static const float sHeightLacunarity;
	static const float sHeightPersistance;

	static const float sDryBaseFrequency;
	static const unsigned int sDryOctaves;
	static const unsigned int sDrySeed;
	static const float sDryLacunarity;
	static const float sDryPersistance;


	static bool sMinMaxInit;
	static float sHeightMin;
	static float sHeightMax;
	static float sDryMin;
	static float sDryMax;
	

	ChunkFactory();
	~ChunkFactory();

	static void GenerateArea(Chunk* aChunk, int aStartX, int aStartY, float aX, float aY, float aIncrement, int aResolution);
	static float GenerateHeightPoint(float aX, float aY);
	static float GenerateDrynessPoint(float aX, float aY);
public:
	static Chunk* GenerateChunk(float aX, float aY, float aSize, int aResolution, unsigned int aLayer, bool aImage = true);
};

