#include "ChunkFactory.h"
#include "TerrainChunk.h"
#include "LayerChunk.h"
#include "Noise.h"
#include <iostream>
#include <SFML/System/Clock.hpp>
#include <thread>
#include <algorithm>

const float ChunkFactory::sHeightBaseFrequency = 1.f / 350000;
const unsigned int ChunkFactory::sHeightOctaves = 10;
//const float ChunkFactory::sHeightBaseFrequency = 1.f / 15000000;
//const unsigned int ChunkFactory::sHeightOctaves = 16;
const unsigned int ChunkFactory::sHeightSeed = (unsigned int)time(NULL);
//const unsigned int ChunkFactory::sHeightSeed = 789432;
const float ChunkFactory::sHeightLacunarity = 2.85f;
const float ChunkFactory::sHeightPersistance = 0.55f;



const float ChunkFactory::sDryBaseFrequency = 1.f / 100000;
//const float ChunkFactory::sDryBaseFrequency = 1.f / 10000000;
const unsigned int ChunkFactory::sDryOctaves = 7;
const unsigned int ChunkFactory::sDrySeed = (unsigned int)time(NULL) + 128;
//const unsigned int ChunkFactory::sDrySeed = 98743267;
const float ChunkFactory::sDryLacunarity = 3.1f;
const float ChunkFactory::sDryPersistance = 0.4f;

bool ChunkFactory::sMinMaxInit = false;
float ChunkFactory::sHeightMax = 1.f;
float ChunkFactory::sHeightMin = 0.f;
float ChunkFactory::sDryMax = 1.f;
float ChunkFactory::sDryMin = 0.f;

const size_t ChunkFactory::sChunkMaxCount = 64;
std::vector<Chunk*> ChunkFactory::sImageChunks = std::vector<Chunk*>();

void ChunkFactory::RemoveChunk(Chunk* aChunk) {
	for (size_t i = 0; i < sImageChunks.size(); i++) {
		if (sImageChunks[i] == aChunk) {
			std::cout << sImageChunks[i]->GetLayer();
			sImageChunks[i] = sImageChunks.back();
			sImageChunks.pop_back();
			break;
		}
	}
}


ChunkFactory::ChunkFactory() {}


ChunkFactory::~ChunkFactory() {}

bool LastTickFirst(Chunk* a, Chunk* b) {
	return a->GetTick() > b->GetTick();
}

Chunk* ChunkFactory::GenerateChunk(float aX, float aY, float aSize, int aResolution, unsigned int aLayer, bool aImage) {

	sf::Clock Timer;

	if (sImageChunks.size() >= sChunkMaxCount) {
		std::sort(sImageChunks.begin(), sImageChunks.end(), LastTickFirst);
		std::cout << "Removing elements... ";
		delete sImageChunks.back();
		std::cout << "\n";
	}

	Chunk* ReturnChunk;
	if (aImage) {
		if (aLayer > 0) {
			LayerChunk* NewLayerChunk = new LayerChunk();
			NewLayerChunk->SetLayer(aLayer);
			NewLayerChunk->SetChunksResolution(4);

			ReturnChunk = NewLayerChunk;
		} else {
			ReturnChunk = new ImageChunk();
		}
		sImageChunks.push_back(ReturnChunk);
	} else {
		ReturnChunk = new TerrainChunk();
	}

	ReturnChunk->SetResolution(aResolution);
	ReturnChunk->SetPosition(aX, aY);
	ReturnChunk->SetSize(aSize);

	float Increment = aSize / aResolution;

	
	if (!sMinMaxInit) {
		sMinMaxInit = true;
		float HeightMax = 0.f;
		float HeightMin = 1.f;
		float DryMax = 0.f;
		float DryMin = 1.f;

		for (int x = 0; x < aResolution; x++) {
			float cX = aX + (float)x * Increment;
			for (int y = 0; y < aResolution; y++) {
				float cY = aY + (float)y * Increment;

				float Height = GenerateHeightPoint(cX, cY);
				float Dryness = GenerateDrynessPoint(cX, cY);

				HeightMax = std::fmaxf(Height, HeightMax);
				HeightMin = std::fminf(Height, HeightMin);

				DryMax = std::fmaxf(Dryness, DryMax);
				DryMin = std::fminf(Dryness, DryMin);
			}
		}

		sHeightMax = HeightMax; 
		sHeightMin = HeightMin;
		sDryMax = DryMax; 
		sDryMin = DryMin;
	}

	const size_t ThreadCountBase = 4;
	const size_t ThreadCount = ThreadCountBase * ThreadCountBase;

	std::thread Threads[ThreadCount];

	for (int i = 0; i < ThreadCount; i++) {
		Threads[i] = std::thread(
			GenerateArea, 
			ReturnChunk, 
			(i % ThreadCountBase) * (aResolution / ThreadCountBase),
			(i / ThreadCountBase) * (aResolution / ThreadCountBase),
			aX, aY, Increment, aResolution / ThreadCountBase
		);
	}

	for (int i = 0; i < ThreadCount; i++) {
		Threads[i].join();
	}
	
	ReturnChunk->ApplyData();
	
	std::cout << "Generated chunk. Layer: " << aLayer << ", X: " << aX << ", Y: " << aY << ". Time: " << Timer.getElapsedTime().asSeconds() << "\n";

	return ReturnChunk;
}

void ChunkFactory::GenerateArea(Chunk* aChunk, int aStartX, int aStartY, float aX, float aY, float aIncrement, int aResolution) {
	for (int x = aStartX; x < aStartX + aResolution; x++) {
		float cX = aX + (float)x * aIncrement;

		for (int y = aStartY; y < aStartY + aResolution; y++) {
			float cY = aY + (float)y * aIncrement;
			
			aChunk->SetData(x, y, Chunk::Height, GenerateHeightPoint(cX, cY));
			aChunk->SetData(x, y, Chunk::Dryness, GenerateDrynessPoint(cX, cY));
		}
	}
}

float ChunkFactory::GenerateHeightPoint(float aX, float aY) {
	float Coords[2]{ aX, aY };
	return std::fminf(std::fmaxf((Noise::Perlin(Coords, 2, sHeightBaseFrequency, sHeightOctaves, sHeightSeed, sHeightLacunarity, sHeightPersistance) - sHeightMin) / (sHeightMax - sHeightMin), 0.f), 0.9999f);
}
float ChunkFactory::GenerateDrynessPoint(float aX, float aY) {
	float Coords[2]{ aX, aY };
	return std::fminf(std::fmaxf((Noise::Perlin(Coords, 2, sDryBaseFrequency, sDryOctaves, sDrySeed, sDryLacunarity, sDryPersistance) - sDryMin) / (sDryMax - sDryMin), 0.f), 0.9999f);
}
