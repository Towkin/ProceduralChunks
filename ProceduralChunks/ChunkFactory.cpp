#include "ChunkFactory.h"
#include "TerrainChunk.h"
#include "ImageLayerChunk.h"
#include "Noise.h"
#include <iostream>
#include <SFML/System/Clock.hpp>
#include <thread>
#include <algorithm>

#include <fstream>
#include <string>

std::map<std::string, float*> ChunkFactory::sFloatValues = std::map<std::string, float*>{
	std::pair<std::string, float*>("fHeightFrequency", &ChunkFactory::sHeightBaseFrequency),
	std::pair<std::string, float*>("fHeightLacunarity", &ChunkFactory::sHeightLacunarity),
	std::pair<std::string, float*>("fHeightPersistance", &ChunkFactory::sHeightPersistance),

	std::pair<std::string, float*>("fDryFrequency", &ChunkFactory::sDryBaseFrequency),
	std::pair<std::string, float*>("fDryLacunarity", &ChunkFactory::sDryLacunarity),
	std::pair<std::string, float*>("fDryPersistance", &ChunkFactory::sDryPersistance)
};

std::map<std::string, unsigned int*> ChunkFactory::sUnsignedIntValues = std::map<std::string, unsigned int*>{
	std::pair<std::string, unsigned int*>("uHeightOctaves", &ChunkFactory::sHeightOctaves),
	std::pair<std::string, unsigned int*>("uHeightSeed", &ChunkFactory::sHeightSeed),

	std::pair<std::string, unsigned int*>("uDryOctaves", &ChunkFactory::sDryOctaves),
	std::pair<std::string, unsigned int*>("uDrySeed", &ChunkFactory::sDrySeed)
};

float ChunkFactory::sHeightBaseFrequency = 1.f / 400000;
unsigned int ChunkFactory::sHeightOctaves = 16;
unsigned int ChunkFactory::sHeightSeed = (unsigned int)time(NULL);
float ChunkFactory::sHeightLacunarity = 2.85f;
float ChunkFactory::sHeightPersistance = 0.45f;

float ChunkFactory::sDryBaseFrequency = 1.f / 100000;
unsigned int ChunkFactory::sDryOctaves = 7;
unsigned int ChunkFactory::sDrySeed = (unsigned int)time(NULL) + 128;
float ChunkFactory::sDryLacunarity = 3.1f;
float ChunkFactory::sDryPersistance = 0.4f;

void ChunkFactory::SetupNoiseSettings() {
	std::vector<std::string> NoiseSettingsLines;

	std::ifstream NoiseSettingsStream;
	NoiseSettingsStream.open("Assets/NoiseSettings.txt");

	if (NoiseSettingsStream.is_open()) {
		std::cout << "\nReading noise settings...\n";

		std::string SettingsLine;
		while (std::getline(NoiseSettingsStream, SettingsLine)) {
			if (SettingsLine.size() < 1 || SettingsLine[0] == '!' || SettingsLine.find('=') == SettingsLine.npos) {
				std::cout << "Skipped line '" + SettingsLine + "'.\n";
				continue;
			}
			std::cout << "Added line '" + SettingsLine + "'.\n";
			NoiseSettingsLines.push_back(SettingsLine);
		}
		NoiseSettingsStream.close();
	} else {
		std::cout << "Couldn't open file NoiseSettings.txt.\n";
	}
	
	for (std::string Line : NoiseSettingsLines) {
		size_t OperatorIndex = Line.find('=');
		std::string Name = Line.substr(0, OperatorIndex);
		std::string Value = Line.substr(OperatorIndex + 1);

		size_t FirstWhiteSpace = Name.find_first_not_of(' ');
		size_t LastNonWhiteSpace = Name.find_last_not_of(' ');
		
		Name = Name.substr(FirstWhiteSpace, LastNonWhiteSpace - FirstWhiteSpace + 1);

		if (sFloatValues.find(Name) != sFloatValues.end()) {
			(*sFloatValues[Name]) = std::stof(Value);
			std::cout << "Found variable " + Name + ", which was assigned value " << std::stof(Value) << ".\n";
		} else if (sUnsignedIntValues.find(Name) != sUnsignedIntValues.end()) {
			(*sUnsignedIntValues[Name]) = std::stoul(Value);
			std::cout << "Found variable " + Name + ", which was assigned value " << std::stoul(Value) << ".\n";
		} else {
			std::cout << "No variable named " + Name + " was found.\n";
		}
	}
}


bool ChunkFactory::sMinMaxInit = false;
float ChunkFactory::sHeightMax = 0.f;
float ChunkFactory::sHeightMin = 1.f;
float ChunkFactory::sDryMax = 0.f;
float ChunkFactory::sDryMin = 1.f;

const size_t ChunkFactory::sChunkMaxCount = 256;
std::vector<Chunk*> ChunkFactory::sRemovableChunks = std::vector<Chunk*>();

void ChunkFactory::RemoveChunk(Chunk* aChunk) {
	for (size_t i = 0; i < sRemovableChunks.size(); i++) {
		if (sRemovableChunks[i] == aChunk) {
			std::cout << "*";
			sRemovableChunks[i] = sRemovableChunks.back();
			sRemovableChunks.pop_back();
			break;
		}
	}
}

bool LastTickFirst(Chunk* a, Chunk* b) {
	return a->GetTick() != b->GetTick() ? a->GetTick() > b->GetTick() : a->GetLayer() < b->GetLayer();
}

Chunk* ChunkFactory::GenerateChunk(float aX, float aY, float aSize, int aResolution, unsigned int aLayer, bool aImage, bool aRemovable) {

	sf::Clock Timer;

	if (aRemovable && sRemovableChunks.size() >= sChunkMaxCount) {
		std::sort(sRemovableChunks.begin(), sRemovableChunks.end(), LastTickFirst);
		std::cout << "Removing elements... ";
		delete sRemovableChunks.back();
		std::cout << "\n";
	}

	Chunk* ReturnChunk;
	if (aImage) {
		if (aLayer > 0) {
			ImageLayerChunk* NewLayerChunk = new ImageLayerChunk();
			NewLayerChunk->SetLayer(aLayer);
			NewLayerChunk->SetChunksResolution(4);

			ReturnChunk = NewLayerChunk;
		} else {
			ReturnChunk = new ImageChunk();
		}
	} else {

		ReturnChunk = new TerrainChunk();
	}

	ReturnChunk->SetResolution(aResolution);
	ReturnChunk->SetPosition(aX, aY);
	ReturnChunk->SetSize(aSize);

	if (aRemovable) {
		sRemovableChunks.push_back(ReturnChunk);
	}

	float Increment = aSize / aResolution;

	
	if (!sMinMaxInit) {
		const size_t MinMaxFinderRes = 1024;

		for (int x = 0; x < MinMaxFinderRes; x++) {
			float cX = aX + (float)x * Increment;
			for (int y = 0; y < MinMaxFinderRes; y++) {
				float cY = aY + (float)y * Increment;

				float Height = GenerateHeightPoint(cX, cY);
				float Dryness = GenerateDrynessPoint(cX, cY);


				sHeightMax = std::fmaxf(Height, sHeightMax);
				sHeightMin = std::fminf(Height, sHeightMin);

				sDryMax = std::fmaxf(Dryness, sDryMax);
				sDryMin = std::fminf(Dryness, sDryMin);
			}
		}

		sMinMaxInit = true;
		std::cout << "Height - Max: " << sHeightMax << ", Min: " << sHeightMin << "\nDryness - Max: " << sDryMax << ", Min: " << sDryMin << ".\n";
	}

	const size_t ThreadCount = 8;

	std::thread Threads[ThreadCount];

	for (int i = 0; i < ThreadCount; i++) {
		Threads[i] = std::thread(
			GenerateArea, 
			ReturnChunk, 
			i * (aResolution / ThreadCount),
			0,
			(i == (ThreadCount - 1) ? aResolution : (i + 1) * (aResolution / ThreadCount)),
			aResolution,
			aX, aY, Increment
		);
	}

	for (int i = 0; i < ThreadCount; i++) {
		Threads[i].join();
	}
	
	ReturnChunk->ApplyData();
	
	std::cout << "Generated chunk. Layer: " << aLayer << ", X: " << aX << ", Y: " << aY << ". Time: " << Timer.getElapsedTime().asSeconds() << "\n";

	return ReturnChunk;
}

void ChunkFactory::GenerateArea(Chunk* aChunk, int aStartX, int aStartY, int aEndX, int aEndY, float aX, float aY, float aIncrement) {
	for (int x = aStartX; x < aEndX; x++) {
		float cX = aX + (float)x * aIncrement;
		
		for (int y = aStartY; y < aEndY; y++) {
			float cY = aY + (float)y * aIncrement;
			
			aChunk->SetData(x, y, Chunk::Height, GenerateHeightPoint(cX, cY));
			aChunk->SetData(x, y, Chunk::Dryness, GenerateDrynessPoint(cX, cY));
		}
	}
}

float ChunkFactory::GenerateHeightPoint(float aX, float aY) {
	float Coords[2]{ aX, aY };
	if (sMinMaxInit) {
		return std::fminf(std::fmaxf((GetModifierHeight(aX, aY) * (Noise::Perlin(Coords, 2, sHeightBaseFrequency, sHeightOctaves, sHeightSeed, sHeightLacunarity, sHeightPersistance) * 0.5f + 0.5f) - sHeightMin) / (sHeightMax - sHeightMin), 0.f), 0.9999f);
	}
	return GetModifierHeight(aX, aY) * (Noise::Perlin(Coords, 2, sHeightBaseFrequency, sHeightOctaves, sHeightSeed, sHeightLacunarity, sHeightPersistance) * 0.5f + 0.5f);
}
float ChunkFactory::GenerateDrynessPoint(float aX, float aY) {
	float Coords[2]{ aX, aY };
	if (sMinMaxInit) {
		return std::fminf(std::fmaxf((GetModifierDryness(aX, aY) * (Noise::Perlin(Coords, 2, sDryBaseFrequency, sDryOctaves, sDrySeed, sDryLacunarity, sDryPersistance) * 0.5f + 0.5f) - sDryMin) / (sDryMax - sDryMin), 0.f), 0.9999f);
	}
	return GetModifierDryness(aX, aY) * (Noise::Perlin(Coords, 2, sDryBaseFrequency, sDryOctaves, sDrySeed, sDryLacunarity, sDryPersistance) * 0.5f + 0.5f);
}


float ChunkFactory::GetModifierHeight(float aX, float aY) {
	return 1.0f;
}

float ChunkFactory::GetModifierDryness(float aX, float aY) {
	return 1.0f;
}