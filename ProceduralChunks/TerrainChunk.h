#pragma once
#include "Chunk.h"

class TerrainChunk :
	public Chunk {
public:
	enum Terrain { 
		Error, 
		SeaAbyss, 
		SeaDeep, 
		SeaNormal,
		SeaShallow,
		SeaTropical,
		Beach,
		Oasis,
		Swamp,
		Forest,
		Grass,
		Savannah,
		Desert,
		BrownMountain,
		GreyMountain,
		DesertMountain,
		Snow, 
		// End with Count
		Count 
	};
private:
	std::vector<TerrainChunk::Terrain> mTerrainData;
	static sf::Image sTerrainMap;
public:
	static std::map<sf::Uint32, TerrainChunk::Terrain> sTerrainColors;
public:
	TerrainChunk();
	virtual ~TerrainChunk();

	static void SetupTerrainColors();

	virtual void SetResolution(size_t aNewResolution) override;

	TerrainChunk::Terrain GetTerrainData(size_t aX, size_t aY) const;
	void SetTerrainData(size_t aX, size_t aY, TerrainChunk::Terrain aType);

	virtual void ApplyData();
};

