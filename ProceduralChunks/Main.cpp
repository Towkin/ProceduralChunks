//#include "ChunkManager.h"
#include "Chunk.h"
#include "LayerChunk.h"
#include "ChunkFactory.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	size_t ChunkRes = 512;

	Chunk* BaseChunk = ChunkFactory::GenerateChunk(0, 0, 250000.f, ChunkRes, 3);

	sf::RenderWindow MainWindow(sf::VideoMode(1024, 800), "Chunks!!!");
	MainWindow.setFramerateLimit(60);
	
	Camera MainCamera(&MainWindow, BaseChunk->GetSize());
	
	sf::Image OverlayImage;
	OverlayImage.create(ChunkRes, ChunkRes);

	sf::Font TextFont;
	TextFont.loadFromFile("falconpunch.ttf");
	

	float WaterHeight = 0.5f;
	size_t WaterCount = 0;
	size_t LandCount = 0;

	for (int x = 0; x < ChunkRes; x++) {
		for (int y = 0; y < ChunkRes; y++) {
			int x1 = std::fminf(x + 1, ChunkRes - 1);
			int y1 = std::fminf(y + 1, ChunkRes - 1);
			float Height00 = BaseChunk->GetData(x, y, Chunk::Height);
			float Height10 = BaseChunk->GetData(x1, y, Chunk::Height);
			float Height01 = BaseChunk->GetData(x, y1, Chunk::Height);
			float Height11 = BaseChunk->GetData(x1, y1, Chunk::Height);
			
			float MeanHeight = (Height00 + Height01 + Height10 + Height11) / 4;

			if (MeanHeight < WaterHeight
				/*Height00 < WaterHeight
				|| Height10 < WaterHeight
				|| Height01 < WaterHeight
				|| Height11 < WaterHeight*/) {
				OverlayImage.setPixel(x, y, sf::Color(255, 0, 0, 64));
				WaterCount++;
			} else {
				OverlayImage.setPixel(x, y, sf::Color(0, 0, 255, 64));
				LandCount++;
			} 
		}
	}

	size_t WaterLandSum = WaterCount + LandCount;
	std::cout << ((float)WaterCount * 100) / WaterLandSum << "% water.\n";

	sf::Texture OverlayTexture;
	OverlayTexture.loadFromImage(OverlayImage);

	sf::RectangleShape MapOverlay(sf::Vector2f(512, 512));
	MapOverlay.setTexture(&OverlayTexture);
	MapOverlay.setScale(sf::Vector2f(BaseChunk->GetSize() / BaseChunk->GetResolution(), BaseChunk->GetSize() / BaseChunk->GetResolution()));

	while (MainWindow.isOpen()) {
		sf::Event WindowEvent;
		while (MainWindow.pollEvent(WindowEvent)) {
			if (WindowEvent.type == sf::Event::Closed) {
				MainWindow.close();
			}
			if (WindowEvent.type == sf::Event::MouseWheelMoved) {
				MainCamera.Zoom(WindowEvent.mouseWheel.delta);
			}
		}

		MainWindow.clear();
		
		MainCamera.Update();
		MainWindow.setView(MainCamera.GetView());

		LayerChunk::sUglyHasLoaded = false;
		BaseChunk->Draw(&MainWindow, sf::FloatRect(MainCamera.GetView().getCenter() - (MainCamera.GetView().getSize() / 2.f), MainCamera.GetView().getSize()));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			MainWindow.draw(MapOverlay);
		}

		float BarSize = std::powf(10.f, std::floorf(std::log10f(MainCamera.GetView().getSize().x * 0.95f)));

		sf::RectangleShape KilometerBar(sf::Vector2f(BarSize, MainCamera.GetView().getSize().y / 50.f));
		
		KilometerBar.setPosition(MainCamera.GetView().getCenter() + sf::Vector2f(0, MainCamera.GetView().getSize().y / 2.f));
		KilometerBar.setOrigin(KilometerBar.getSize().x / 2.f, MainCamera.GetView().getSize().y * 0.04f);
		KilometerBar.setFillColor(sf::Color(64, 64, 64));

		sf::Text KilometerText;

		KilometerText.setCharacterSize(16);
		KilometerText.setScale(MainCamera.GetView().getSize().y * 0.001f, MainCamera.GetView().getSize().y * 0.001f);
		KilometerText.setFont(TextFont);
		std::string MeterString = std::to_string((int)BarSize) + " m";
		int NumberBegin = 0;
		for (int i = MeterString.size() - 1; i >= 0; i--) {
			if (NumberBegin == 0) {
				if (MeterString[i] == '0') {
					NumberBegin++;
				}
				continue;
			}

			if (++NumberBegin % 3 == 0) {
				MeterString.insert(MeterString.begin() + i, ' ');
			}
		}

		KilometerText.setString(MeterString);

		KilometerText.setPosition(MainCamera.GetView().getCenter() + sf::Vector2f(0, MainCamera.GetView().getSize().y / 2.1f));
		KilometerText.setOrigin(MeterString.size() * 6, 16);

		MainWindow.draw(KilometerBar);
		MainWindow.draw(KilometerText);

		//MainWindow.draw(MapDraw);
		//MainWindow.draw(bleh);

		MainWindow.display();

		
	}

	return 0;
}