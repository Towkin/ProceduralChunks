#pragma once
#include "Chunk.h"
#include <string>

class TerrainChunk :
	public Chunk {
private:
	std::vector<std::string*> mTerrainData;
	static sf::Image sTerrainMap;
	
public:
	static std::map<sf::Uint32, std::string> sTerrainColors;
	static std::string sErrorTerrain;

public:
	TerrainChunk();
	virtual ~TerrainChunk();

	static void SetupTerrainColors();
	virtual void SetResolution(size_t aNewResolution) override;

	const std::string& GetTerrainData(size_t aX, size_t aY) const;
	void SetTerrainData(size_t aX, size_t aY, std::string* aType);

	virtual void ApplyData();
};

