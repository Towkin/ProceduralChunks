#include "TerrainChunk.h"
#include <fstream>
#include <iostream>

sf::Image TerrainChunk::sTerrainMap;
std::string TerrainChunk::sErrorTerrain = "Error";
std::map<sf::Uint32, std::string> TerrainChunk::sTerrainColors;

void TerrainChunk::SetupTerrainColors() {
	sTerrainMap.loadFromFile("Assets/TerrainMap.png");
	
	std::ifstream TerrainColorStream;

	TerrainColorStream.open("Assets/TerrainColor.txt");
	if (TerrainColorStream.is_open()) {
		std::string ColorString;
		while (std::getline(TerrainColorStream, ColorString)) {
			if (ColorString.size() < 1 || ColorString[0] == '!') {
				continue;
			}
			size_t TerrainNameLength = ColorString.find('#');
			if (TerrainNameLength == std::string::npos) {
				continue;
			}
			
			std::string TerrainName = ColorString.substr(0, TerrainNameLength);
			std::string TerrainColorValues = ColorString.substr(TerrainNameLength + 1);
			if (TerrainColorValues.size() < 6) {
				std::cout << "Failed to read values for '" + TerrainName + "'!\n";
				continue;
			}

			sf::Uint8 R = std::stoi(TerrainColorValues.substr(0, 2), nullptr, 16);
			sf::Uint8 G = std::stoi(TerrainColorValues.substr(2, 2), nullptr, 16);
			sf::Uint8 B = std::stoi(TerrainColorValues.substr(4, 2), nullptr, 16);

			std::cout << "Name: '" + TerrainName + "', Values: '" + std::to_string(R) + "', '" + std::to_string(G) + "', '" + std::to_string(B) + "' ('" + TerrainColorValues + "')\n";

			sTerrainColors[sf::Color(R, G, B).toInteger()] = TerrainName;
		}
	} else {
		std::cout << "TerrainColor.txt read failed.\n";
	}
}


TerrainChunk::TerrainChunk():
	Chunk(),
	mTerrainData()
{}


TerrainChunk::~TerrainChunk() {}


void TerrainChunk::SetResolution(size_t aNewResolution) {
	Chunk::SetResolution(aNewResolution);
	mTerrainData.resize(aNewResolution * aNewResolution);
}

const std::string& TerrainChunk::GetTerrainData(size_t aX, size_t aY) const {
	return *mTerrainData[GetIndex(aX, aY)];
}
void TerrainChunk::SetTerrainData(size_t aX, size_t aY, std::string* aType) {
	mTerrainData[GetIndex(aX, aY)] = aType;
}

void TerrainChunk::ApplyData() {
	for (size_t x = 0; x < GetResolution(); x++) {
		for (size_t y = 0; y < GetResolution(); y++) {
			float Height = GetData(x, y, Chunk::DataType::Height);
			float Dryness = GetData(x, y, Chunk::DataType::Dryness);

			sf::Color PointColor = sTerrainMap.getPixel(Height * sTerrainMap.getSize().x, Dryness * sTerrainMap.getSize().y);
			if (sTerrainColors.find(PointColor.toInteger()) == sTerrainColors.end()) {
				SetTerrainData(x, y, &sErrorTerrain);
			} else {
				SetTerrainData(x, y, &sTerrainColors[PointColor.toInteger()]);
			}
		}
	}
}
