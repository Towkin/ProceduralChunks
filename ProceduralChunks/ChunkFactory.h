#pragma once
#include <vector>
#include <map>

class Chunk;
class ChunkFactory
{
private:
	ChunkFactory() = delete;
	~ChunkFactory() = delete;

	static std::map<std::string, float*> sFloatValues;
	static std::map<std::string, unsigned int*> sUnsignedIntValues;

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


	static bool sMinMaxInit;
	static float sHeightMin;
	static float sHeightMax;
	static float sDryMin;
	static float sDryMax;
	
	static const size_t sChunkMaxCount;
	static std::vector<Chunk*> sRemovableChunks;

	
	static void GenerateArea(Chunk* aChunk, int aStartX, int aStartY, int aEndX, int aEndY, float aX, float aY, float aIncrement);
	static float GenerateHeightPoint(float aX, float aY);
	static float GenerateDrynessPoint(float aX, float aY);

	static float GetModifierHeight(float aX, float aY);
	static float GetModifierDryness(float aX, float aY);
public:
	static void SetupNoiseSettings();

	static Chunk* GenerateChunk(float aX, float aY, float aSize, int aResolution, unsigned int aLayer, bool aImage = true, bool aRemovable = true);

	static void RemoveChunk(Chunk* aChunk);
};

