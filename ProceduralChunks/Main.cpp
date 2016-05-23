//#include "ChunkManager.h"
#include "TerrainChunk.h"
#include "LayerChunk.h"
#include "ChunkFactory.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	size_t ChunkRes = 512;
	float WorldSize = 250000.f;

	TerrainChunk* DataChunk = (TerrainChunk*)ChunkFactory::GenerateChunk(0, 0, WorldSize, ChunkRes * 4, 0, false);
	Chunk* BaseChunk = ChunkFactory::GenerateChunk(0, 0, WorldSize, ChunkRes, 2);

	sf::RenderWindow MainWindow(sf::VideoMode(1024, 800), "Chunks!!!");
	MainWindow.setFramerateLimit(60);
	
	Camera MainCamera(&MainWindow, BaseChunk->GetSize());
	
	sf::Image OverlayImage;
	OverlayImage.create(DataChunk->GetResolution(), DataChunk->GetResolution());

	sf::Font TextFont;
	TextFont.loadFromFile("falconpunch.ttf");
	
	
	sf::Color TerrainColors[TerrainChunk::Terrain::Count];
	sf::Uint8 Opacity = 128;
	TerrainColors[TerrainChunk::Terrain::Error] =			sf::Color(255, 0, 0, Opacity);
	TerrainColors[TerrainChunk::Terrain::DeepWater] =		sf::Color(0, 0, 128, Opacity);
	TerrainColors[TerrainChunk::Terrain::Water] =			sf::Color(0, 0, 255, Opacity);
	TerrainColors[TerrainChunk::Terrain::Forest] =			sf::Color(0, 128, 0, Opacity);
	TerrainColors[TerrainChunk::Terrain::ForestMountain] =	sf::Color(96, 128, 64, Opacity);
	TerrainColors[TerrainChunk::Terrain::Grass] =			sf::Color(0, 192, 64, Opacity);
	TerrainColors[TerrainChunk::Terrain::Mountain] =		sf::Color(64, 64, 64, Opacity);
	TerrainColors[TerrainChunk::Terrain::Desert] =			sf::Color(255, 255, 0, Opacity);
	TerrainColors[TerrainChunk::Terrain::DesertMountain] =	sf::Color(128, 96, 64, Opacity);
	TerrainColors[TerrainChunk::Terrain::MountainTop] =		sf::Color(192, 192, 192, Opacity);

	//size_t WaterCount = 0;
	//size_t LandCount = 0;

	for (size_t x = 0; x < DataChunk->GetResolution(); x++) {
		for (size_t y = 0; y < DataChunk->GetResolution(); y++) {
			TerrainChunk::Terrain TerrainType = DataChunk->GetTerrainData(x, y);
			OverlayImage.setPixel(x, y, TerrainColors[TerrainType]);
		}
	}

	//size_t WaterLandSum = WaterCount + LandCount;
	//std::cout << ((float)WaterCount * 100) / WaterLandSum << "% water.\n";

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