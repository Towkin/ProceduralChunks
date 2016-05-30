#pragma once
#include "Chunk.h"
#include <string>

class TerrainChunk :
	public Chunk {
private:
	static size_t sTerrainIndexCounter;
	//std::vector<std::string*> mTerrainData;
	std::vector<size_t> mTerrainData;
	static sf::Image sTerrainMap;
	static std::map<std::string, size_t> sTerrainIndex;
	
public:
	//static std::map<sf::Uint32, std::string> sTerrainColors;
	static std::map<sf::Uint32, size_t> sTerrainColors;
	static std::string sErrorTerrain;
	static sf::Color sErrorColor;

public:
	TerrainChunk();
	virtual ~TerrainChunk();
	static void SetupTerrainColors();
	
	static const sf::Color GetTerrainColor(const std::string& aType);
	static const sf::Color GetTerrainColor(const size_t aType);
	virtual void SetResolution(size_t aNewResolution) override;

	//const std::string& GetTerrainData(size_t aX, size_t aY) const;
	//void SetTerrainData(size_t aX, size_t aY, std::string* aType);
	const size_t GetTerrainData(size_t aX, size_t aY) const;
	void SetTerrainData(size_t aX, size_t aY, const std::string& aType);
	void SetTerrainData(size_t aX, size_t aY, size_t aType);

	virtual void ApplyData();
};

