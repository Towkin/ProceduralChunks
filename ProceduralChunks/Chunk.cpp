#include "Chunk.h"
#include "ChunkFactory.h"
#include <iostream>

unsigned int Chunk::sMasterTick = 0;

bool Chunk::ValidCoordinates(size_t aX, size_t aY) const
{
	if (aX >= GetResolution() 
	||  aY >= GetResolution()) {
		return false;
	}
	return true;
}

float Chunk::GetData(size_t aX, size_t aY, DataType aType) const
{
	return mData.find(aType)->second[GetIndex(aX, aY)];
	//if (ValidCoordinates(aX, aY)) {
	//	const std::vector<float>& RawData = mData.find(aType)->second;
	//	return RawData[aX + aY * GetResolution()];
	//}
	//
	//return 0.0f;
}

void Chunk::SetData(size_t aX, size_t aY, DataType aType, float aValue)
{
	mData[aType][GetIndex(aX, aY)] = aValue;
	//if (ValidCoordinates(aX, aY)) {
	//	mData[aType][aX + aY * GetResolution()] = aValue;
	//}
}

void Chunk::SetResolution(size_t aNewResolution)
{
	mResolution = aNewResolution;
	mData[DataType::Dryness].resize(GetResolution() * GetResolution());
	mData[DataType::Height].resize(GetResolution() * GetResolution());
}

size_t Chunk::GetIndex(size_t aX, size_t aY) const {
	return aX * GetResolution() + aY;
}



void Chunk::Tick() {
	mLastTick = sMasterTick;
}

Chunk::Chunk() :
	mData(std::map<DataType, std::vector<float>>()),
	mResolution(0)
{}


Chunk::~Chunk() {
	if (GetParent()) {
		GetParent()->RemoveChild(this);
	}
	
	ChunkFactory::RemoveChunk(this);
}
