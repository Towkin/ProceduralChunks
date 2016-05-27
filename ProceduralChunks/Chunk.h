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

private:
	float mX, mY;
	float mChunkSize;

	std::map<DataType, std::vector<float>> mData;
	size_t mResolution;
	
	Chunk* mParent;

	static unsigned int sMasterTick;
	unsigned int mLastTick;
protected:
	bool ValidCoordinates(size_t aX, size_t aY) const;
	size_t GetIndex(size_t aX, size_t aY) const;

public:
	float GetData(size_t aX, size_t aY, DataType aType) const;
	void SetData(size_t aX, size_t aY, DataType aType, float aValue);
	size_t GetResolution() const { return mResolution; }
	virtual void SetResolution(size_t aNewResolution);

	
	void SetPosition(float aX, float aY) { mX = aX; mY = aY; }
	float GetX() const { return mX; }
	float GetY() const { return mY; }

	float GetSize() const { return mChunkSize; }
	void SetSize(float aNewSize) { mChunkSize = aNewSize; }
	
	Chunk* GetParent() const { return mParent; }
	void SetParent(Chunk* aParent) { mParent = aParent; }

	virtual void RemoveChild(Chunk* aChild) {}


	virtual void ApplyData() {}
	virtual unsigned int GetLayer() const { return 0; }
	virtual void Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) {}
	virtual void Tick();

	unsigned int GetTick() const { return mLastTick; }

	static void MasterTick() { sMasterTick++; }

	Chunk();
	virtual ~Chunk();
};

