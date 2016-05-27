#pragma once

#include <math.h>
#include <map>

/// <summary></summary>
/// <param name=""></param>

class Noise {
private:
	Noise() = delete;
	~Noise() = delete;
protected:
	// Hash values and functions
	static std::map<unsigned int, const int*> sHashes;
	static const int sHashMask;
	static const float sHashFactor;
	static const int* GetHash(unsigned int aSeed);
	

	// Help values and functions
	/// <summary>Smoothing method to smooth values in range [0...1], using the polynomial function f(x) = 6x^5 - 15x^4 + 10x^3.</summary>
	/// <param name="x">Input value to smooth.</param>
	static float Smooth(float x);
	/// <summary>Simple unclamped linear interpolation.</summary>
	/// <param name="a">Value at t = 0.</param>
	/// <param name="b">Value at t = 1.</param>
	/// <param name="t">Interpolation alpha.</param>
	static float Lerp(float a, float b, float t);
	/// <summary>Fast float to int mathematically correct floor conversion. Works with any float value in integer range.</summary>
	/// <param name="x">The float value to be floored and converted to int.</param>
	static int IntFloorFast(float x);
	/// <summary>Precalculated constant of the square root of 2.</summary>
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
	
	static float Perlin(float x, float aFrequency, unsigned int aSeed = 128);
	static float Perlin(float x, float y, float aFrequency, unsigned int aSeed = 128);
	static float Perlin(float x, float y, float z, float aFrequency, unsigned int aSeed = 128);
	
	/// <summary>Complex Perlin Noise method, calling multiple noise functions and returning the sum in range [-1...1].</summary>
	/// <param name="aCoords">A C-style array containing the coordinates to calculate noise for. Must contain at least as many elements as aDimensions.</param>
	/// <param name="aDimensions">The number of dimensions to do Perlin Noise in, can be [1], [2] or [3].</param>
	/// <param name="aFrequency">The frequency of the first "wave". Hgih frequency = Noisy. Is used as base for later octaves.</param>
	/// <param name="aOctaves">The number of noise calculations to run on this spot.</param>
	/// <param name="aSeed">The seed to use when calculating each octave of noise. Note: each seed generates it's own hash-set, avoid switching too often in runtime.</param>
	/// <param name="aLacunarity">A multiplier, multiplying the last frequency once per octave.</param>
	/// <param name="aPersistance">How much each additional octave after the first matters.</param>
	static float Perlin(float aCoords[], size_t aDimensions, float aFrequency, unsigned int aOctaves, unsigned int aSeed = 128, float aLacunarity = 2.f, float aPersistance = 0.5f);
};

