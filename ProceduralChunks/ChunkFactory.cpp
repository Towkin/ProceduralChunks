#include "ChunkFactory.h"
#include "LayerChunk.h"
#include "Noise.h"
#include <iostream>
#include <time.h>

unsigned int ChunkFactory::sHeightSeed = (unsigned int)time(NULL);
unsigned int ChunkFactory::sDrySeed = (unsigned int)time(NULL) + 128;


ChunkFactory::ChunkFactory() {}


ChunkFactory::~ChunkFactory() {}

Chunk* ChunkFactory::GenerateChunk(float aX, float aY, float aSize, int aResolution, unsigned int aLayer) {

	Chunk* ReturnChunk;
	if (aLayer > 0) {
		LayerChunk* NewLayerChunk = new LayerChunk();
		NewLayerChunk->SetLayer(aLayer);
		NewLayerChunk->SetChunksResolution(4);

		ReturnChunk = NewLayerChunk;
	} else {
		ReturnChunk = new Chunk();
	}

	ReturnChunk->SetPosition(aX, aY);
	ReturnChunk->SetSize(aSize);
	ReturnChunk->SetResolution(aResolution);
	
	float Increment = aSize / aResolution;
	for (int x = 0; x < aResolution; x++) {
		for (int y = 0; y < aResolution; y++) {
			
			float cX = aX + (float)x * Increment;
			float cY = aY + (float)y * Increment;

			float Coords[2] { cX, cY };

			//float Height = (float)x / aResolution;
			//float Dryness = (float)y / aResolution;

			float Height =	Noise::Perlin(Coords, 2, 0.25f, 8, sHeightSeed, 0.20f, 1.85f);
			float Dryness = Noise::Perlin(Coords, 2, 0.05f, 6, sDrySeed, 0.025f, 3.f);
			
			ReturnChunk->SetData(x, y, Chunk::Height, Height);
			ReturnChunk->SetData(x, y, Chunk::Dryness, Dryness);

			//std::cout << "Value " << Value << "\n";
		}
	}
	
	ReturnChunk->ApplyData();

	std::cout << "Generated chunk. Layer: " << aLayer << ", X: " << aX << ", Y: " << aY << ".\n";

	return ReturnChunk;
}
