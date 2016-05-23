#include "TerrainChunk.h"


sf::Image TerrainChunk::sTerrainMap;
std::map<sf::Uint32, TerrainChunk::Terrain> TerrainChunk::sTerrainColors;

void TerrainChunk::SetupTerrainColors() {
	sTerrainMap.loadFromFile("TerrainMap.png");
	
	sTerrainColors[sf::Color(0x0b, 0x27, 0x47).toInteger()] = Terrain::SeaAbyss;
	sTerrainColors[sf::Color(0x2e, 0x59, 0x8b).toInteger()] = Terrain::SeaDeep;
	sTerrainColors[sf::Color(0x60, 0x85, 0xb0).toInteger()] = Terrain::SeaNormal;
	sTerrainColors[sf::Color(0x97, 0xbe, 0xeb).toInteger()] = Terrain::SeaShallow;
	sTerrainColors[sf::Color(0x8e, 0xdd, 0xdd).toInteger()] = Terrain::SeaTropical;

	sTerrainColors[sf::Color(0xff, 0xff, 0x00).toInteger()] = Terrain::Beach;
	sTerrainColors[sf::Color(0x61, 0xcf, 0x7e).toInteger()] = Terrain::Oasis;
	sTerrainColors[sf::Color(0x24, 0x85, 0x51).toInteger()] = Terrain::Swamp;
	sTerrainColors[sf::Color(0x00, 0x6c, 0x1d).toInteger()] = Terrain::Forest;
	sTerrainColors[sf::Color(0x3b, 0xc6, 0x35).toInteger()] = Terrain::Grass;
	sTerrainColors[sf::Color(0x80, 0xc6, 0x35).toInteger()] = Terrain::Savannah;
	sTerrainColors[sf::Color(0xe8, 0xce, 0x53).toInteger()] = Terrain::Desert;
	sTerrainColors[sf::Color(0x6c, 0x63, 0x41).toInteger()] = Terrain::BrownMountain;
	sTerrainColors[sf::Color(0x69, 0x69, 0x69).toInteger()] = Terrain::GreyMountain;
	sTerrainColors[sf::Color(0x8e, 0x87, 0x6d).toInteger()] = Terrain::DesertMountain;
	sTerrainColors[sf::Color(0xdd, 0xdd, 0xdd).toInteger()] = Terrain::Snow;
}


TerrainChunk::TerrainChunk() {}


TerrainChunk::~TerrainChunk() {}


void TerrainChunk::SetResolution(size_t aNewResolution) {
	Chunk::SetResolution(aNewResolution);
	mTerrainData.resize(aNewResolution * aNewResolution);
}

TerrainChunk::Terrain TerrainChunk::GetTerrainData(size_t aX, size_t aY) const {
	return mTerrainData[GetIndex(aX, aY)];
}

void TerrainChunk::SetTerrainData(size_t aX, size_t aY, TerrainChunk::Terrain aType) {
	mTerrainData[GetIndex(aX, aY)] = aType;
}

void TerrainChunk::ApplyData() {
	for (size_t x = 0; x < GetResolution(); x++) {
		for (size_t y = 0; y < GetResolution(); y++) {
			float Height = GetData(x, y, Chunk::DataType::Height);
			float Dryness = GetData(x, y, Chunk::DataType::Dryness);

			sf::Color PointColor = sTerrainMap.getPixel(Height * sTerrainMap.getSize().x, Dryness * sTerrainMap.getSize().y);
			SetTerrainData(x, y, sTerrainColors[PointColor.toInteger()]);

			//if (Height < 0.25f) { // Deep Water
			//	SetTerrainData(x, y, DeepWater);
			//} else if (Height < 0.5f) { // Water
			//	SetTerrainData(x, y, Water);
			//} else if (Height < 0.75f) { // Grass, Desert, Forest
			//	if (Dryness < 0.33f) { // Forest
			//		SetTerrainData(x, y, Forest);
			//	} else if(Dryness < 0.75f) { // Grass
			//		SetTerrainData(x, y, Grass);
			//	} else { // Desert
			//		SetTerrainData(x, y, Desert);
			//	}
			//} else if (Height < 0.95f) { // Mountain, DesertMountain, ForestMountain
			//	if (Dryness < 0.33f) { // ForestMountain
			//		SetTerrainData(x, y, ForestMountain);
			//	} else if (Dryness < 0.66f) { // Mountain
			//		SetTerrainData(x, y, Mountain);
			//	} else { // DesertMountain
			//		SetTerrainData(x, y, DesertMountain);
			//	}
			//} else { // MountainTop
			//	SetTerrainData(x, y, MountainTop);
			//}
		}
	}
}
