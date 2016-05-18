#include "Chunk.h"
#include <iostream>

float Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}
sf::Uint8 Lerp(sf::Uint8 a, sf::Uint8 b, float t) {
	return a + (b - a) * t;
}
sf::Color LerpColors(sf::Color& aColorA, sf::Color& aColorB, float t) {
	return sf::Color(Lerp(aColorA.r, aColorB.r, t), Lerp(aColorA.g, aColorB.g, t), Lerp(aColorA.b, aColorB.b, t), Lerp(aColorA.a, aColorB.a, t));
}

bool Chunk::sShouldLerpColors = false;

sf::Image Chunk::GetMapColors() {
	sf::Image ReturnImage;
	ReturnImage.loadFromFile("ColorMap.png");
	
	return ReturnImage;
}
sf::Image Chunk::sMapColors = Chunk::GetMapColors();

bool Chunk::ValidCoordinates(int aX, int aY) const
{
	if (aX < 0 || aX >= GetResolution() 
	||  aY < 0 || aY >= GetResolution()) {
		return false;
	}
	return true;
}

float Chunk::GetData(int aX, int aY, DataType aType) const
{
	if (ValidCoordinates(aX, aY)) {
		const std::vector<float>& RawData = mData.find(aType)->second;
		return RawData[aX + aY * GetResolution()];
	}
	
	return 0.0f;
}

void Chunk::SetData(int aX, int aY, DataType aType, float aValue)
{
	if (ValidCoordinates(aX, aY)) {
		mData[aType][aX + aY * GetResolution()] = aValue;
	}
}

void Chunk::SetResolution(size_t aNewResolution)
{
	mResolution = aNewResolution;
	mData[DataType::Dryness].resize(GetResolution() * GetResolution());
	mData[DataType::Height].resize(GetResolution() * GetResolution());
}

void Chunk::ApplyData() {
	mImage.create(GetResolution(), GetResolution(), sf::Color::Black);

	for (int x = 0; x < GetResolution(); x++) {
		for (int y = 0; y < GetResolution(); y++) {
			float HeightValue = GetData(x, y, DataType::Height);
			float DryValue = GetData(x, y, DataType::Dryness);

			if (sShouldLerpColors) {
				float HeightValueLerp = HeightValue * sMapColors.getSize().x;
				int HeightValueMin = std::floorf(HeightValueLerp);
				HeightValueLerp -= HeightValueMin;
				int HeightValueMax = HeightValueMin + 1;

				float DryValueLerp = DryValue * sMapColors.getSize().y;
				int DryValueMin = std::floorf(DryValueLerp);
				DryValueLerp -= DryValueMin;
				int DryValueMax = DryValueMin + 1;

				mImage.setPixel(
					x, y, //sMapColors.getPixel(HeightValue * sMapColors.getSize().x, DryValue * sMapColors.getSize().y)
					LerpColors(
						LerpColors(
							sMapColors.getPixel(HeightValueMin, DryValueMin),
							sMapColors.getPixel(HeightValueMax, DryValueMin),
							HeightValueLerp
							),
						LerpColors(
							sMapColors.getPixel(HeightValueMin, DryValueMax),
							sMapColors.getPixel(HeightValueMax, DryValueMax),
							HeightValueLerp
							),
						DryValueLerp
					)
				);
			} else {
				mImage.setPixel(x, y, sMapColors.getPixel(HeightValue * sMapColors.getSize().x, DryValue * sMapColors.getSize().y));
			}
		}
	}

	mTexture.loadFromImage(mImage);
	mDrawRectangle.setTexture(&mTexture, true);
	mDrawRectangle.setSize((sf::Vector2f)mTexture.getSize());
	mDrawRectangle.setPosition(mX, mY);
	mDrawRectangle.setScale(sf::Vector2f(mChunkSize / mTexture.getSize().x, mChunkSize / mTexture.getSize().y));
}

void Chunk::Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) {
	aRenderer->draw(mDrawRectangle);
}

Chunk::Chunk() :
	mData(std::map<DataType, std::vector<float>>()),
	mResolution(0),
	mImage(sf::Image())
{}


Chunk::~Chunk() {}
