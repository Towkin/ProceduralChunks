#include "ChunkFactory.h"
#include "LayerChunk.h"
#include "Noise.h"
#include <iostream>
#include <time.h>




float ChunkFactory::sHeightBaseFrequency = 1.f / 50000;
unsigned int ChunkFactory::sHeightOctaves = 8;
unsigned int ChunkFactory::sHeightSeed = (unsigned int)time(NULL);
//unsigned int ChunkFactory::sHeightSeed = 789432;
float ChunkFactory::sHeightLacunarity = 2.45f;
float ChunkFactory::sHeightPersistance = 0.43f;



float ChunkFactory::sDryBaseFrequency = 1.f / 100000;
unsigned int ChunkFactory::sDryOctaves = 6;
unsigned int ChunkFactory::sDrySeed = (unsigned int)time(NULL) + 128;
//unsigned int ChunkFactory::sDrySeed = 98743267;
float ChunkFactory::sDryLacunarity = 3.1f;
float ChunkFactory::sDryPersistance = 0.4f;



float ChunkFactory::sHeightMax = 0.f;
float ChunkFactory::sHeightMin = 1.f;

float ChunkFactory::sDryMax = 0.f;
float ChunkFactory::sDryMin = 1.f;

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

	if (sHeightMax == 0.f && sHeightMin == 1.f &&
		sDryMax == 0.f && sDryMin == 1.f) {
		for (int x = 0; x < aResolution; x++) {
			for (int y = 0; y < aResolution; y++) {

				float cX = aX + (float)x * Increment;
				float cY = aY + (float)y * Increment;

				float Coords[2]{ cX, cY };

				//float Height = (float)x / aResolution;
				//float Dryness = (float)y / aResolution;

				float Height =	Noise::Perlin(Coords, 2, sHeightBaseFrequency, sHeightOctaves, sHeightSeed, sHeightLacunarity, sHeightPersistance);
				float Dryness = Noise::Perlin(Coords, 2, sDryBaseFrequency, sDryOctaves, sDrySeed, sDryLacunarity, sDryPersistance);

				sHeightMax = std::fmaxf(Height, sHeightMax);
				sHeightMin = std::fminf(Height, sHeightMin);

				sDryMax = std::fmaxf(Dryness, sDryMax);
				sDryMin = std::fminf(Dryness, sDryMin);
				
				
			}
		}
		sHeightMax += 0.025f;
		sHeightMin -= 0.025f;

		sDryMax += 0.025f;
		sDryMin -= 0.025f;

		std::cout << "Static\n Height - Max: " << sHeightMax << ", Min: " << sHeightMin << "\n Dryness - Max: " << sDryMax << ", Min: " << sDryMin << "\n";
	}

	float HeightMax = 0.f;
	float HeightMin = 1.f;

	float DryMax = 0.f;
	float DryMin = 1.f;


	for (int x = 0; x < aResolution; x++) {
		for (int y = 0; y < aResolution; y++) {
			
			float cX = aX + (float)x * Increment;
			float cY = aY + (float)y * Increment;

			float Coords[2] { cX, cY };

			//float Height = (float)x / aResolution;
			//float Dryness = (float)y / aResolution;

			float Height =	(Noise::Perlin(Coords, 2, sHeightBaseFrequency, sHeightOctaves, sHeightSeed, sHeightLacunarity, sHeightPersistance) - sHeightMin) / (sHeightMax - sHeightMin);
			float Dryness = (Noise::Perlin(Coords, 2, sDryBaseFrequency, sDryOctaves, sDrySeed, sDryLacunarity, sDryPersistance) - sDryMin) / (sDryMax - sDryMin);
			
			HeightMax = std::fmaxf(HeightMax, Height);
			HeightMin = std::fminf(HeightMin, Height);

			DryMax = std::fmaxf(DryMax, Dryness);
			DryMin = std::fminf(DryMin, Dryness);

			ReturnChunk->SetData(x, y, Chunk::Height, Height);
			ReturnChunk->SetData(x, y, Chunk::Dryness, Dryness);

			//std::cout << "Value " << Value << "\n";
		}
	}
	
	std::cout << "Generated chunk. Layer: " << aLayer << ", X: " << aX << ", Y: " << aY << ".\n";


	ReturnChunk->ApplyData();

	
	return ReturnChunk;
}
