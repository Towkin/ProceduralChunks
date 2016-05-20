#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Chunk
{
public:
	enum DataType { Height, Dryness };

	const static bool sShouldLerpColors;

private:
	float mX, mY;
	float mChunkSize;

	std::map<DataType, std::vector<float>> mData;
	size_t mResolution;

	sf::RectangleShape mDrawRectangle;
	sf::Texture mTexture;
	sf::Image mImage;

	static sf::Image sMapColors;
	static sf::Image GetMapColors();

protected:
	bool ValidCoordinates(int aX, int aY) const;
	

public:
	float GetData(int aX, int aY, DataType aType) const;
	void SetData(int aX, int aY, DataType aType, float aValue);
	size_t GetResolution() const { return mResolution; }
	void SetResolution(size_t aNewResolution);

	void SetPosition(float aX, float aY) { mX = aX; mY = aY; }
	float GetX() const { return mX; }
	float GetY() const { return mY; }

	float GetSize() const { return mChunkSize; }
	void SetSize(float aNewSize) { mChunkSize = aNewSize; }

	const sf::Image& GetImage() const { return mImage; }
	void ApplyData();

	virtual unsigned int GetLayer() const { return 0; }

	virtual void Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect);

	Chunk();
	~Chunk();
};

