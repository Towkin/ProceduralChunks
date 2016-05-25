#include "ImageChunk.h"
#include <thread>

float Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}
sf::Uint8 Lerp(sf::Uint8 a, sf::Uint8 b, float t) {
	return a + (b - a) * t;
}
sf::Color LerpColors(sf::Color& aColorA, sf::Color& aColorB, float t) {
	return sf::Color(Lerp(aColorA.r, aColorB.r, t), Lerp(aColorA.g, aColorB.g, t), Lerp(aColorA.b, aColorB.b, t), Lerp(aColorA.a, aColorB.a, t));
}

const bool ImageChunk::sShouldLerpColors = false;

sf::Image ImageChunk::GetMapColors() {
	sf::Image ReturnImage;
	ReturnImage.loadFromFile("ColorMap.png");

	return ReturnImage;
}
sf::Image ImageChunk::sMapColors = ImageChunk::GetMapColors();


ImageChunk::ImageChunk() :
	mImage(sf::Image())
{}


ImageChunk::~ImageChunk() {}

void ImageChunk::ApplyData() {
	mImage.create(GetResolution(), GetResolution(), sf::Color::Black);

	const size_t ThreadCount = 16;
	std::thread ImageThreads[ThreadCount];

	int IncrementX = std::ceilf(GetResolution() / ThreadCount);

	for (int i = 0; i < ThreadCount; i++) {
		size_t MinX = i * IncrementX;
		size_t MaxX = (size_t)std::fminf((1 + i) * IncrementX, GetResolution());
		size_t MinY = 0;
		size_t MaxY = GetResolution();

		//ApplyArea(MinX, MinY, MaxX, MaxY);

		ImageThreads[i] = std::thread(
			ApplyArea, 
			this,
			MinX, 
			MinY, 
			MaxX, 
			MaxY
		);
	}
	for (int i = 0; i < ThreadCount; i++) {
		ImageThreads[i].join();
	}

	mTexture.loadFromImage(mImage);
	mDrawRectangle.setTexture(&mTexture, true);
	mDrawRectangle.setSize((sf::Vector2f)mTexture.getSize());
	mDrawRectangle.setPosition(GetX(), GetY());
	mDrawRectangle.setScale(sf::Vector2f(GetSize() / mTexture.getSize().x, GetSize() / mTexture.getSize().y));
}

void ImageChunk::ApplyArea(ImageChunk* aChunk, size_t aStartX, size_t aStartY, size_t aEndX, size_t aEndY) {
	for (int x = aStartX; x < aEndX; x++) {
		for (int y = aStartY; y < aEndY; y++) {
			
			//if(x < 2 || y < 2) {
			//mImage.setPixel(x, y, sf::Color());
			//continue;
			//}


			float HeightValue = aChunk->GetData(x, y, DataType::Height);
			float DryValue = aChunk->GetData(x, y, DataType::Dryness);
			sf::Color PixelColor;

			if (sShouldLerpColors) {
				float HeightValueLerp = HeightValue * (sMapColors.getSize().x - 1);
				int HeightValueMin = std::floorf(HeightValueLerp);
				HeightValueLerp -= HeightValueMin;
				int HeightValueMax = HeightValueMin + 1;

				float DryValueLerp = DryValue * (sMapColors.getSize().y - 1);
				int DryValueMin = std::floorf(DryValueLerp);
				DryValueLerp -= DryValueMin;
				int DryValueMax = DryValueMin + 1;

				PixelColor = LerpColors(
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
				);
			} else {
				PixelColor = sMapColors.getPixel(HeightValue * sMapColors.getSize().x, DryValue * sMapColors.getSize().y);
				//PixelColor = sf::Color(128, 128, 128);
				//PixelColor = sf::Color(255 * HeightValue, 255 * HeightValue, 255 * HeightValue);

				// Shadow test

				//if (HeightValue > 0.5f) {
				//	const size_t PixelDistance = std::fmaxf(1, (100 * aChunk->GetResolution()) / aChunk->GetSize());//std::ceilf(((ShadowLength / GetSize()) * GetResolution()));

				//	float HeightX0 = aChunk->GetData(std::fmaxf(x - PixelDistance, 0), y, DataType::Height);
				//	float HeightX1 = aChunk->GetData(std::fminf(x + PixelDistance, aChunk->GetResolution() - 1), y, DataType::Height);

				//	float HeightY0 = aChunk->GetData(x, std::fmaxf(y - PixelDistance, 0), DataType::Height);
				//	float HeightY1 = aChunk->GetData(x, std::fminf(y + PixelDistance, aChunk->GetResolution() - 1), DataType::Height);

				//	const float WeightX = 1.f;
				//	const float WeightY = 0.75f;

				//	float DarkenValue = 1.f - std::fminf(std::fmaxf(0.f, (2000.f * (WeightX * (HeightX0 - HeightX1) + WeightY * (HeightY0 - HeightY1)) / aChunk->GetResolution()) * (HeightValue - 0.5f) * 2.f - 0.005f), 1.f);

				//	//PixelColor.r = std::fminf(255, PixelColor.r * DarkenValue);
				//	//PixelColor.g = std::fminf(255, PixelColor.g * DarkenValue);
				//	//PixelColor.b = std::fminf(255, PixelColor.b * DarkenValue);

				//	PixelColor.r *= DarkenValue;
				//	PixelColor.g *= DarkenValue;
				//	PixelColor.b *= DarkenValue;
				//}
			}

			aChunk->mImage.setPixel(x, y, PixelColor);
		}
	}
}

void ImageChunk::Draw(sf::RenderTarget* aRenderer, sf::FloatRect aRenderRect) {
	aRenderer->draw(mDrawRectangle);
	Tick();
}