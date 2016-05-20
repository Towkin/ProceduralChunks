#pragma once

#include <math.h>
#include <map>

class Noise {
private:
	Noise();
	~Noise();
protected:

	// Hash values and functions
	static std::map<unsigned int, const int*> sHashes;
	static const int sHashMask;
	static const float sHashFactor;
	static const int* GetHash(unsigned int aSeed);
	

	// Help values and functions
	static float Smooth(float x);
	static float Lerp(float a, float b, float t);
	static const float sSqrt2;

	// Value noise 1D, 2D and 3D
	static float RawValueNoise(float x, const int aHash[]);
	static float RawValueNoise(float x, float y, const int aHash[]);
	static float RawValueNoise(float x, float y, float z, const int aHash[]);

	// Failed and slow test
	static float RawValueNoise(float aPoint[], size_t aDimensions, const int aHash[]);

	// Vectors and gradients required for Perlin noise
	struct Vector2 {
		float x, y;
		Vector2() :
			x(0), y(0)
		{}
		Vector2(float aX, float aY) :
			x(aX), y(aY)
		{}
		float Dot(Vector2 aOther) const { return x * aOther.x + y * aOther.y; }
		float Dot(float aX, float aY) const { return x * aX + y * aY; }
		float Magnitude() const { return sqrtf(x * x + y * y); }
		Vector2 Normalize() const { float m = this->Magnitude(); return Vector2(x / m, y / m); }
	};
	struct Vector3 {
		float x, y, z;
		Vector3() :
			x(0), y(0), z(0)
		{}
		Vector3(float aX, float aY, float aZ) :
			x(aX), y(aY), z(aZ)
		{}
		
		float Dot(Vector3 aOther) const { return x * aOther.x + y * aOther.y + z * aOther.z; }
		float Dot(float aX, float aY, float aZ) const { return x * aX + y * aY + z * aZ; }
		float Magnitude() const { return sqrtf(x * x + y * y + z * z); }
		Vector3 Normalize() const { float m = this->Magnitude(); return Vector3(x / m, y / m, z / m); }
	};

	static const float sGradients1D[];
	static const int sGradienentMask1D;
	static const Vector2 sGradients2D[];
	static const int sGradienentMask2D;
	static const Vector3 sGradients3D[];
	static const int sGradienentMask3D;

	// Perlin noise 1D, 2D and 3D
	static float RawPerlinNoise(float x, const int aHash[]);
	static float RawPerlinNoise(float x, float y, const int aHash[]);
	static float RawPerlinNoise(float x, float y, float z, const int aHash[]);

public:
	static float Value(float x, float aFrequency, unsigned int aSeed = 128);
	static float Value(float x, float y, float aFrequency, unsigned int aSeed = 128);
	static float Value(float x, float y, float z, float aFrequency, unsigned int aSeed = 128);

	static float Value(float aCoords[], size_t aDimensions, float aFrequency, unsigned int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);

	//static float Value(float x, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);
	//static float Value(float x, float y, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);
	//static float Value(float x, float y, float z, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);

	
	static float Perlin(float x, float aFrequency, unsigned int aSeed = 128);
	static float Perlin(float x, float y, float aFrequency, unsigned int aSeed = 128);
	static float Perlin(float x, float y, float z, float aFrequency, unsigned int aSeed = 128);
	
	static float Perlin(float aCoords[], size_t aDimensions, float aFrequency, unsigned int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);
	
	//static float Perlin(float x, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);
	//static float Perlin(float x, float y, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);
	//static float Perlin(float x, float y, float z, float aFrequency, int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);

};

