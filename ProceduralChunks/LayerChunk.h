#pragma once
#include "Chunk.h"

class LayerChunk :
	public Chunk {
public:
	LayerChunk();
	~LayerChunk();

	virtual unsigned int GetLayer() const override { return mLayer; }
	void SetLayer(unsigned int aNewLayer) { mLayer = aNewLayer; }

	virtual void Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) override;

	Chunk* GetChunk(size_t aX, size_t aY);
	
	float GetChildSize() const { return GetSize() / mChunksResolution; }
	size_t GetChunksResolution() const { return mChunksResolution; }
	void SetChunksResolution(size_t aNewResolution);

protected:
	bool ValidChunk(size_t aX, size_t aY) const;

private:
	std::vector<Chunk*> mChunks;
	size_t mChunksResolution;
	
	unsigned int mLayer;
};

