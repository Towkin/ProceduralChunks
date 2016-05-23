#include "TerrainChunk.h"



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

			if (Height < 0.25f) { // Deep Water
				SetTerrainData(x, y, DeepWater);
			} else if (Height < 0.5f) { // Water
				SetTerrainData(x, y, Water);
			} else if (Height < 0.75f) { // Grass, Desert, Forest
				if (Dryness < 0.33f) { // Forest
					SetTerrainData(x, y, Forest);
				} else if(Dryness < 0.75f) { // Grass
					SetTerrainData(x, y, Grass);
				} else { // Desert
					SetTerrainData(x, y, Desert);
				}
			} else if (Height < 0.95f) { // Mountain, DesertMountain, ForestMountain
				if (Dryness < 0.33f) { // ForestMountain
					SetTerrainData(x, y, ForestMountain);
				} else if (Dryness < 0.66f) { // Mountain
					SetTerrainData(x, y, Mountain);
				} else { // DesertMountain
					SetTerrainData(x, y, DesertMountain);
				}
			} else { // MountainTop
				SetTerrainData(x, y, MountainTop);
			}
		}
	}
}
