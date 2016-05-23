#pragma once
#include "Chunk.h"

class TerrainChunk :
	public Chunk {
public:
	enum Terrain { Error, DeepWater, Water, Forest, Grass, Desert, ForestMountain, Mountain, DesertMountain, MountainTop, Count };
private:
	std::vector<TerrainChunk::Terrain> mTerrainData;
public:
	TerrainChunk();
	~TerrainChunk();

	virtual void SetResolution(size_t aNewResolution) override;

	TerrainChunk::Terrain GetTerrainData(size_t aX, size_t aY) const;
	void SetTerrainData(size_t aX, size_t aY, TerrainChunk::Terrain aType);

	virtual void ApplyData();
};

