#include "Noise.h"
#include <vector>
#include <random>
#include <algorithm>
#include <array>

Noise::Noise() {}
Noise::~Noise() {}

//int Noise::sHash[512]{
//	151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
//	140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
//	247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
//	57, 177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
//	74, 165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
//	60, 211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
//	65,  25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
//	200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
//	52, 217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
//	207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
//	119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
//	129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
//	218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
//	81,  51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
//	184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
//	222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180,
//
//	151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
//	140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
//	247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
//	57, 177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
//	74, 165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
//	60, 211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
//	65,  25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
//	200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
//	52, 217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
//	207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
//	119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
//	129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
//	218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
//	81,  51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
//	184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
//	222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180
//};

std::map<unsigned int, const int*> Noise::sHashes = std::map<unsigned int, const int*>();

const int Noise::sHashMask = 255;
const float Noise::sHashFactor = 1.f / Noise::sHashMask;
const int* Noise::GetHash(unsigned int aSeed) {
	if (sHashes.find(aSeed) == sHashes.end()) {
		const size_t HashSize = (sHashMask + 1) * 2;
		const size_t HashSizeHalf = HashSize / 2;

		// Stupid? I think so... But I could see no better way to keep the values outside this context.
		std::array<int, HashSize>& Hash = (*new std::array<int, HashSize>());

		// Initiate values
		for (int i = 0; i < HashSizeHalf; i++) {
			Hash[i] = i;
		}
		// Scramble values
		std::shuffle(Hash.begin(), Hash.begin() + HashSizeHalf, std::default_random_engine(aSeed));

		// Dublicate 
		for (int i = 0; i < HashSizeHalf; i++) {
			Hash[i + HashSizeHalf] = Hash[i];
		}

		sHashes[aSeed] = Hash.data();
	}

	return sHashes[aSeed];
}

const float Noise::sSqrt2 = 1.41421356237f;

const float Noise::sGradients1D[2] { 
	1.f, 
	-1.f 
};
const int Noise::sGradienentMask1D = 1;
const Noise::Vector2 Noise::sGradients2D[8] {
	Noise::Vector2( 1.f,  0.f),
	Noise::Vector2(-1.f,  0.f),
	Noise::Vector2( 0.f,  1.f),
	Noise::Vector2( 0.f, -1.f),
	Noise::Vector2( 1.f,  1.f).Normalize(),
	Noise::Vector2(-1.f,  1.f).Normalize(),
	Noise::Vector2( 1.f, -1.f).Normalize(),
	Noise::Vector2(-1.f, -1.f).Normalize()
};
const int Noise::sGradienentMask2D = 7;
const Noise::Vector3 Noise::sGradients3D[16] {
	Noise::Vector3( 1.f,  1.f,  0.f),
	Noise::Vector3(-1.f,  1.f,  0.f),
	Noise::Vector3( 1.f, -1.f,  0.f),
	Noise::Vector3(-1.f, -1.f,  0.f),

	Noise::Vector3( 1.f,  0.f,  1.f),
	Noise::Vector3(-1.f,  0.f,  1.f),
	Noise::Vector3( 1.f,  0.f, -1.f),
	Noise::Vector3(-1.f,  0.f, -1.f),

	Noise::Vector3( 0.f,  1.f,  1.f),
	Noise::Vector3( 0.f, -1.f,  1.f),
	Noise::Vector3( 0.f,  1.f, -1.f),
	Noise::Vector3( 0.f, -1.f, -1.f),

	Noise::Vector3( 1.f,  1.f,  0.f),
	Noise::Vector3(-1.f,  1.f,  0.f),
	Noise::Vector3( 0.f, -1.f,  1.f),
	Noise::Vector3( 0.f, -1.f, -1.f)
};
const int Noise::sGradienentMask3D = 15;



float Noise::Smooth(float x) {
	return x * x * x * (x * (x * 6.f - 15.f) + 10.f); 
}
float Noise::Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}


float Noise::RawValueNoise(float x, const int aHash[]) {
	int HashPoint = (int)floorf(x);
	float LerpValue = Smooth(x - HashPoint);
	HashPoint &= sHashMask;

	return Lerp(
		aHash[HashPoint],
		aHash[HashPoint + 1],
		LerpValue
	) * sHashFactor;
}
float Noise::RawValueNoise(float x, float y, const int aHash[]) {
	int HashPoint0 = (int)floorf(x);
	float LerpX = Smooth(x - HashPoint0);
	HashPoint0 &= sHashMask;
	int HashPoint1 = HashPoint0 + 1;

	int Hash0 = aHash[HashPoint0];
	int Hash1 = aHash[HashPoint1];

	HashPoint0 = (int)floorf(y);
	float LerpY = Smooth(y - HashPoint0);
	HashPoint0 &= sHashMask;
	HashPoint1 = HashPoint0 + 1;

	int Hash00 = aHash[Hash0 + HashPoint0];
	int Hash01 = aHash[Hash0 + HashPoint1];
	int Hash10 = aHash[Hash1 + HashPoint0];
	int Hash11 = aHash[Hash1 + HashPoint1];

	return Lerp(
		Lerp(
			Hash00,
			Hash10,
			LerpX
		), 
		Lerp(
			Hash01, 
			Hash11, 
			LerpX
		),
		LerpY
	) * sHashFactor;
}
float Noise::RawValueNoise(float x, float y, float z, const int aHash[]) {
	
	int HashPoint0 = (int)floorf(x);
	float LerpX = Smooth(x - HashPoint0);
	HashPoint0 &= sHashMask;
	int HashPoint1 = HashPoint0 + 1;

	int Hash0 = aHash[HashPoint0];
	int Hash1 = aHash[HashPoint1];

	HashPoint0 = (int)floorf(y);
	float LerpY = Smooth(y - HashPoint0);
	HashPoint0 &= sHashMask;
	HashPoint1 = HashPoint0 + 1;

	int Hash00 = aHash[Hash0 + HashPoint0];
	int Hash01 = aHash[Hash0 + HashPoint1];
	int Hash10 = aHash[Hash1 + HashPoint0];
	int Hash11 = aHash[Hash1 + HashPoint1];

	HashPoint0 = (int)floorf(z);
	float LerpZ = Smooth(z - HashPoint0);
	HashPoint0 &= sHashMask;
	HashPoint1 = HashPoint0 + 1;

	int Hash000 = aHash[Hash00 + HashPoint0];
	int Hash001 = aHash[Hash00 + HashPoint1];

	int Hash010 = aHash[Hash01 + HashPoint0];
	int Hash011 = aHash[Hash01 + HashPoint1];

	int Hash100 = aHash[Hash10 + HashPoint0];
	int Hash101 = aHash[Hash10 + HashPoint1];
	
	int Hash110 = aHash[Hash11 + HashPoint0];
	int Hash111 = aHash[Hash11 + HashPoint1];

	return 
	Lerp(
		Lerp(
			Lerp(
				Hash000,
				Hash100,
				LerpX
			),
			Lerp(
				Hash010,
				Hash110,
				LerpX
			),
			LerpY
		),
		Lerp(
			Lerp(
				Hash001,
				Hash101,
				LerpX
			),
			Lerp(
				Hash011,
				Hash111,
				LerpX
			),
			LerpY
		),
		LerpZ
	) * sHashFactor;
}

// Test for any number of dimensions: Failure for performance reasons.
float Noise::RawValueNoise(float aPoint[], size_t aDimensions, const int aHash[]) {
	if (aDimensions == 0) {
		return 0.f;
	}

	std::vector<std::vector<int>> HashPoint = std::vector<std::vector<int>>(aDimensions);
	std::vector<float> LerpAmount = std::vector<float>(aDimensions);

	// HashPoint and LerpAmount gathering - note that it's HashPoint[dimension][0...1]
	int HashPointMask = 1;
	for (int i = 0; i < aDimensions; i++) {
		HashPoint[i].resize(2);
		HashPoint[i][0] = (int)floorf(aPoint[i]);
		LerpAmount[i] = aPoint[i] - HashPoint[i][0];
		HashPoint[i][0] &= sHashMask;
		HashPoint[i][1] = HashPoint[i][0] + 1;
	}

	std::vector<std::vector<int>> HashValues = std::vector<std::vector<int>>(aDimensions);

	// Hash value gathering.
	for (int i = 0; i < aDimensions; i++) {
		size_t RequiredSize = 2;
		for (int j = 0; j < i; j++) {
			RequiredSize *= 2;
		}
		HashValues[i].resize(RequiredSize);

		if (i > 0) {
			int LastMask = HashValues[i - 1].size() - 1;

			for (int j = 0; j < RequiredSize; j ++) {
				HashValues[i][j] = aHash[HashValues[i - 1][j / 2] + HashPoint[i][j & HashPointMask]];
			}
		} else {
			HashValues[0][0] = aHash[HashPoint[0][0]];
			HashValues[0][1] = aHash[HashPoint[0][1]];
		}
	}
	
	std::vector<std::vector<float>> LerpValue = std::vector<std::vector<float>>(aDimensions);

	// LerpValue gathering.
	for (int i = aDimensions - 1; i >= 0; i--) {
		LerpValue[i].resize(HashValues[i].size() / 2);

		if (i < aDimensions - 1) {
			for (int j = 0; j < LerpValue[i].size(); j++) {
				LerpValue[i][j] = Lerp(LerpValue[i + 1][j * 2 + 0], LerpValue[i + 1][j * 2 + 1], LerpAmount[aDimensions - i - 1]);
			}
		} else {
			for (int j = 0; j < LerpValue[i].size(); j ++) {
				LerpValue[i][j] = Lerp(HashValues[i][j * 2 + 0], HashValues[i][j * 2 + 1], LerpAmount[aDimensions - i - 1]);
			}
		}
	}

	return LerpValue[0][0] * sHashFactor;
}


float Noise::RawPerlinNoise(float x, const int aHash[]) {
	int HashPoint0 = (int)floorf(x);
	float Decimal0 = x - HashPoint0;
	float Decimal1 = Decimal0 - 1.f;
	float LerpValue = Smooth(Decimal0);

	HashPoint0 &= sHashMask;
	int HashPoint1 = HashPoint0;

	float Gradient0 = sGradients1D[aHash[HashPoint0] & sGradienentMask1D];
	float Gradient1 = sGradients1D[aHash[HashPoint1] & sGradienentMask1D];

	float Velocity0 = Gradient0 * Decimal0;
	float Velocity1 = Gradient1 * Decimal1;
	
	return Lerp(
		Velocity0,
		Velocity1,
		LerpValue
	) + 0.5f;
}
float Noise::RawPerlinNoise(float x, float y, const int aHash[]) {
	
	int HashPoint0 = (int)floorf(x);
	float DecimalX0 = x - HashPoint0;
	float DecimalX1 = DecimalX0 - 1.f;
	float LerpX = Smooth(DecimalX0);
	HashPoint0 &= sHashMask;
	int HashPoint1 = HashPoint0 + 1;

	int Hash0 = aHash[HashPoint0];
	int Hash1 = aHash[HashPoint1];

	HashPoint0 = (int)floorf(y);
	float DecimalY0 = y - HashPoint0;
	float DecimalY1 = DecimalY0 - 1.f;
	float LerpY = Smooth(DecimalY0);
	HashPoint0 &= sHashMask;
	HashPoint1 = HashPoint0 + 1;

	float Velocity00 = sGradients2D[aHash[Hash0 + HashPoint0] & sGradienentMask2D].Dot(DecimalX0, DecimalY0);
	float Velocity01 = sGradients2D[aHash[Hash0 + HashPoint1] & sGradienentMask2D].Dot(DecimalX0, DecimalY1);
	float Velocity10 = sGradients2D[aHash[Hash1 + HashPoint0] & sGradienentMask2D].Dot(DecimalX1, DecimalY0);
	float Velocity11 = sGradients2D[aHash[Hash1 + HashPoint1] & sGradienentMask2D].Dot(DecimalX1, DecimalY1);

	return 
	Lerp(
		Lerp(
			Velocity00,
			Velocity10,
			LerpX
		),
		Lerp(
			Velocity01,
			Velocity11,
			LerpX
		),
		LerpY
	) * sSqrt2 / 2.f + 0.5f;
}
float Noise::RawPerlinNoise(float x, float y, float z, const int aHash[]) {
	int HashPoint0 = (int)floorf(x);
	float DecimalX0 = x - HashPoint0;
	float DecimalX1 = DecimalX0 - 1.f;
	float LerpX = Smooth(DecimalX0);
	HashPoint0 &= sHashMask;
	int HashPoint1 = HashPoint0 + 1;

	int Hash0 = aHash[HashPoint0];
	int Hash1 = aHash[HashPoint1];

	HashPoint0 = (int)floorf(y);
	float DecimalY0 = y - HashPoint0;
	float DecimalY1 = DecimalY0 - 1.f;
	float LerpY = Smooth(DecimalY0);
	HashPoint0 &= sHashMask;
	HashPoint1 = HashPoint0 + 1;

	int Hash00 = aHash[Hash0 + HashPoint0];
	int Hash01 = aHash[Hash0 + HashPoint1];
	
	int Hash10 = aHash[Hash1 + HashPoint0];
	int Hash11 = aHash[Hash1 + HashPoint1];

	HashPoint0 = (int)floorf(z);
	float DecimalZ0 = z - HashPoint0;
	float DecimalZ1 = DecimalZ0 - 1.f;
	float LerpZ = Smooth(DecimalZ0);
	HashPoint0 &= sHashMask;
	HashPoint1 = HashPoint0 + 1;

	float Velocity000 = sGradients3D[aHash[Hash00 + HashPoint0] & sGradienentMask3D].Dot(DecimalX0, DecimalY0, DecimalZ0);
	float Velocity001 = sGradients3D[aHash[Hash00 + HashPoint1] & sGradienentMask3D].Dot(DecimalX0, DecimalY0, DecimalZ1);
	float Velocity010 = sGradients3D[aHash[Hash01 + HashPoint0] & sGradienentMask3D].Dot(DecimalX0, DecimalY1, DecimalZ0);
	float Velocity011 = sGradients3D[aHash[Hash01 + HashPoint1] & sGradienentMask3D].Dot(DecimalX0, DecimalY1, DecimalZ1);

	float Velocity100 = sGradients3D[aHash[Hash10 + HashPoint0] & sGradienentMask3D].Dot(DecimalX1, DecimalY0, DecimalZ0);
	float Velocity101 = sGradients3D[aHash[Hash10 + HashPoint1] & sGradienentMask3D].Dot(DecimalX1, DecimalY0, DecimalZ1);
	float Velocity110 = sGradients3D[aHash[Hash11 + HashPoint0] & sGradienentMask3D].Dot(DecimalX1, DecimalY1, DecimalZ0);
	float Velocity111 = sGradients3D[aHash[Hash11 + HashPoint1] & sGradienentMask3D].Dot(DecimalX1, DecimalY1, DecimalZ1);

	return
	Lerp(
		Lerp(
			Lerp(
				Velocity000,
				Velocity100,
				LerpX
			),
			Lerp(
				Velocity010,
				Velocity110,
				LerpX
			),
			LerpY
		),
		Lerp(
			Lerp(
				Velocity001,
				Velocity101,
				LerpX
			),
			Lerp(
				Velocity011,
				Velocity111,
				LerpX
			),
			LerpY
		),
		LerpZ
	) / 2.f + 0.5f;
}

float Noise::Value(float aCoords[], size_t aDimensions, float aFrequency, unsigned int aOctaves, unsigned int aSeed, float aLacunarity, float aPersistance) {
	float Sum = 0.f;
	switch (aDimensions) {
		case 1:
			Sum = Value(aCoords[0], aCoords[1], aFrequency, aSeed);
			break;
		case 2:
			Sum = Value(aCoords[0], aCoords[1], aFrequency, aSeed);
			break;
		case 3:
			Sum = Value(aCoords[0], aCoords[1], aFrequency, aSeed);
			break;
		default:
			break;
	}
	
	float Amplitude = 1.f;
	float Range = 1.f;

	for (int i = 1; i < aOctaves; i++) {
		aFrequency *= aLacunarity;
		Amplitude *= aPersistance;
		Range += Amplitude;
		
		switch (aDimensions) {
			case 1:
				Sum += Value(aCoords[0], aCoords[1], aFrequency, aSeed) * Amplitude;
				break;
			case 2:
				Sum += Value(aCoords[0], aCoords[1], aFrequency, aSeed) * Amplitude;
				break;
			case 3:
				Sum += Value(aCoords[0], aCoords[1], aFrequency, aSeed) * Amplitude;
				break;
			default:
				break;
		}
	}
	
	return Sum / Range;
}

float Noise::Perlin(float aCoords[], size_t aDimensions, float aFrequency, unsigned int aOctaves, unsigned int aSeed, float aLacunarity, float aPersistance) {
	float Sum = 0.f;
	switch (aDimensions) {
		case 1:
			Sum = Perlin(aCoords[0], aCoords[1], aFrequency, aSeed);
			break;
		case 2:
			Sum = Perlin(aCoords[0], aCoords[1], aFrequency, aSeed);
			break;
		case 3:
			Sum = Perlin(aCoords[0], aCoords[1], aFrequency, aSeed);
			break;
		default:
			break;
	}

	float Amplitude = 1.f;
	float Range = 1.f;

	for (int i = 1; i < aOctaves; i++) {
		aFrequency *= aLacunarity;
		Amplitude *= aPersistance;
		Range += Amplitude;

		switch (aDimensions) {
			case 1:
				Sum += Perlin(aCoords[0], aCoords[1], aFrequency, aSeed) * Amplitude;
				break;
			case 2:
				Sum += Perlin(aCoords[0], aCoords[1], aFrequency, aSeed) * Amplitude;
				break;
			case 3:
				Sum += Perlin(aCoords[0], aCoords[1], aFrequency, aSeed) * Amplitude;
				break;
			default:
				break;
		}
	}

	return Sum / Range;
}



//float Noise::Value(float x, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity, float aPersistance) {
//	float Sum = Value(x, aFrequency, aSeed);
//	float Amplitude = 1.f;
//	float Range = 1.f;
//
//	for (int i = 1; i < aOctaves; i++) {
//		aFrequency *= aLacunarity;
//		Amplitude *= aPersistance;
//		Range += Amplitude;
//		Sum += Value(x, aFrequency, aSeed) * Amplitude;
//	}
//	
//	return Sum / Range;
//}
//float Noise::Value(float x, float y, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity, float aPersistance) {
//	float Sum = Value(x, y, aFrequency, aSeed);
//	float Amplitude = 1.f;
//	float Range = 1.f;
//
//	for (int i = 1; i < aOctaves; i++) {
//		aFrequency *= aLacunarity;
//		Amplitude *= aPersistance;
//		Range += Amplitude;
//		Sum += Value(x, y, aFrequency, aSeed) * Amplitude;
//	}
//
//	return Sum / Range;
//}
//float Noise::Value(float x, float y, float z, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity, float aPersistance) {
//	float Sum = Value(x, y, z, aFrequency, aSeed);
//	float Amplitude = 1.f;
//	float Range = 1.f;
//
//	for (int i = 1; i < aOctaves; i++) {
//		aFrequency *= aLacunarity;
//		Amplitude *= aPersistance;
//		Range += Amplitude;
//		Sum += Value(x, y, z, aFrequency, aSeed) * Amplitude;
//	}
//
//	return Sum / Range;
//}

//float Noise::Perlin(float x, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity, float aPersistance) {
//	float Sum = Perlin(x, aFrequency, aSeed);
//	float Amplitude = 1.f;
//	float Range = 1.f;
//
//	for (int i = 1; i < aOctaves; i++) {
//		aFrequency *= aLacunarity;
//		Amplitude *= aPersistance;
//		Range += Amplitude;
//		Sum += Perlin(x, aFrequency, aSeed) * Amplitude;
//	}
//
//	return Sum / Range;
//}
//float Noise::Perlin(float x, float y, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity, float aPersistance) {
//	float Sum = Perlin(x, y, aFrequency, aSeed);
//	float Amplitude = 1.f;
//	float Range = 1.f;
//
//	for (int i = 1; i < aOctaves; i++) {
//		aFrequency *= aLacunarity;
//		Amplitude *= aPersistance;
//		Range += Amplitude;
//		Sum += Perlin(x, y, aFrequency, aSeed) * Amplitude;
//	}
//
//	return Sum / Range;
//}
//float Noise::Perlin(float x, float y, float z, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity, float aPersistance) {
//	float Sum = Perlin(x, y, z, aFrequency, aSeed);
//	float Amplitude = 1.f;
//	float Range = 1.f;
//
//	for (int i = 1; i < aOctaves; i++) {
//		aFrequency *= aLacunarity;
//		Amplitude *= aPersistance;
//		Range += Amplitude;
//		Sum += Perlin(x, y, z, aFrequency, aSeed) * Amplitude;
//	}
//
//	return Sum / Range;
//}
