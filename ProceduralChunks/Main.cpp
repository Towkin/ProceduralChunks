//#include "ChunkManager.h"
#include "Chunk.h"
#include "ChunkFactory.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	//ChunkManager Manager;

	Chunk* BaseChunk = ChunkFactory::GenerateChunk(0, 0, 100000.f, 512, 3);


	sf::RenderWindow MainWindow(sf::VideoMode(1024, 800), "Chunks!!!");
	MainWindow.setFramerateLimit(60);
	
	Camera MainCamera(&MainWindow);
	
	sf::Image OverlayImage;
	OverlayImage.create(512, 512);

	for (int x = 0; x < 512; x++) {
		for (int y = 0; y < 512; y++) {
			float Height = BaseChunk->GetData(x, y, Chunk::Height);
			
			if (Height < 0.42f) {
				OverlayImage.setPixel(x, y, sf::Color(255, 0, 0, 64));
			} else if (Height < 0.85f) {
				OverlayImage.setPixel(x, y, sf::Color(0, 0, 255, 64));
			} else {
				OverlayImage.setPixel(x, y, sf::Color(255, 0, 0, 64));
			}
		}
	}

	sf::Texture OverlayTexture;
	OverlayTexture.loadFromImage(OverlayImage);

	sf::RectangleShape MapOverlay(sf::Vector2f(512, 512));
	MapOverlay.setTexture(&OverlayTexture);
	MapOverlay.setScale(sf::Vector2f(100000.f / 512.f, 100000.f / 512.f));

	int MouseDelta = 0;

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

		BaseChunk->Draw(&MainWindow, sf::FloatRect(MainCamera.GetView().getCenter() - (MainCamera.GetView().getSize() / 2.f), MainCamera.GetView().getSize()));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			MainWindow.draw(MapOverlay);
		}
		

		//MainWindow.draw(MapDraw);
		//MainWindow.draw(bleh);

		MainWindow.display();
	}

	return 0;
}